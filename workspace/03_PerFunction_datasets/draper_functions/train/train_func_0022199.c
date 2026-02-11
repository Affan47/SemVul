ParseSmiles(const char *ptr, int prev)
  {
    char *name;
    int atomid;
    int next;
    int type;
    int ch;

    type = 0;
    while( (ch = *ptr++) )
      {
        switch( ch )
          {
          case('-'): type = BF_SINGLE;
            break;
          case('='): type = BF_DOUBLE;
            break;
          case('#'): type = BF_TRIPLE;
            break;
          case('^'): type = BF_SINGLE|BF_AROMATIC;
            break;
          case('~'): type = BF_DOUBLE|BF_AROMATIC;
            break;

          case(')'): return( ptr );
          case('.'): prev = -1;
            break;
          case('('): ptr = ParseSmiles(ptr,prev);
            break;

          default:
            atomid = ch-'0';
            while( isdigit(*ptr) )
              atomid = (atomid*10)+(*ptr++)-'0';

            for( next=0; next<MonoAtomCount; next++ )
              if( MonoAtom[next].atomid == atomid )
                break;

            if( next == MonoAtomCount )
              {
                name = ChainsAtomName[atomid];
                MonoAtom[next].elem = IdentifyElement(name);
                MonoAtom[next].atomid = atomid;
                MonoAtom[next].bcount = 0;
                MonoAtomCount++;
              }

            if( prev != -1 )
              {
                MonoBond[MonoBondCount].flag = type;
                MonoBond[MonoBondCount].src = prev;
                MonoBond[MonoBondCount].dst = next;
                MonoBondCount++;

                MonoAtom[prev].bcount++;
                MonoAtom[next].bcount++;
              }
            prev = next;
          }
      }
    return( ptr-1 );
  }
