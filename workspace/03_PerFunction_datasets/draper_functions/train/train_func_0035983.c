printbuff()
{ char *spot,*s,*d;

  if ( buff[0] == 0 ) return;
  spot = buff;
  while ( (spot = strchr(spot,'&')) != NULL )
  { s = spot + 1;
     if ( kb_strnicmp(spot+1,"lt;",3) == 0 ) { *spot = '<'; s = spot+4; }
     if ( kb_strnicmp(spot+1,"gt;",3) == 0 ) { *spot = '>'; s = spot+4; }
     if ( kb_strnicmp(spot+1,"amp;",4) == 0 ) { *spot = '&'; s = spot+5; }
     if ( kb_strnicmp(spot+1,"quot;",5) == 0 ) { *spot = '"'; s = spot+6; }
     for ( d = spot+1 ; *s ; s++,d++ ) *d = *s;
     *d = 0;
     spot++;
  }
  if ( pre_flag ) { outstring(buff); outstring("\n"); }
  else
  { char *cur;
     char *b;

     char *src,*dest;


     if ( pre_flag == 0 )
     {
        for ( src = buff; *src ; src++ ) if ( *src == '\t' ) *src = ' ';
        src = buff; while ( *src == ' ' ) src++ ;
        for ( dest = buff, src = buff; *src ; src++ )
        { if ( (*src == ' ') && (dest[-1] == ' ') ) continue;
          else *(dest++) = *src;
        }
     } else dest = buff + strlen(buff);
     *dest = 0; dest[1] = 0;


     for ( cur = buff; *cur ; cur = b+1 )
     {
        for ( b = cur; *b && (b < cur+LINESIZE) ; b++ )
          if ( *b == '\n' ) break;
        if ( *b == '\n' )
        { *b = 0; outstring(cur); outstring("\n"); continue; }


        b = cur + LINESIZE;
        if ( b < dest )
        {
          while ( (*b != ' ') && (b > cur) ) b--;
          if ( b == cur ) { b = cur + LINESIZE; }
        }
        else b = dest;
        *b = 0;
        outstring(cur); outstring("\n");
     }
  }
  buff[0] = 0;
}
