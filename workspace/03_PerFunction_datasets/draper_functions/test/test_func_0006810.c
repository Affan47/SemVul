ParseSimpleAtomPrimitive( void )
  {
    switch( *LexPtr++ )
      {
      case '*':
        return BuildAtomLeaf(AL_CONST,true);
      case 'A':
        return BuildAtomLeaf(AL_AROM,false);
      case 'B':
        if( *LexPtr == 'r' )
          {
            LexPtr++;
            return GenerateElement(35);
          }
        return GenerateElement(5);
      case 'C':
        if( *LexPtr == 'l' )
          {
            LexPtr++;
            return GenerateElement(17);
          }
        return GenerateAromElem(6,false);
      case 'F':
        return GenerateElement( 9);
      case 'I':
        return GenerateElement(53);
      case 'N':
        return GenerateAromElem(7,false);
      case 'O':
        return GenerateAromElem(8,false);
      case 'P':
        return GenerateAromElem(15, false);
      case 'S':
        return GenerateAromElem(16,false);
      case 'a':
        if( *LexPtr == 's' )
          {
            LexPtr++;
            return GenerateAromElem(33, true);
          }
        return BuildAtomLeaf(AL_AROM,true);
      case 'c':
        return GenerateAromElem( 6,true);
      case 'n':
        return GenerateAromElem( 7,true);
      case 'o':
        return GenerateAromElem( 8,true);
      case 'p':
        return GenerateAromElem(15,true);
      case 's':
        if( *LexPtr == 'e' )
          {
            LexPtr++;
            return GenerateAromElem(34, true);
          }
        return GenerateAromElem(16,true);
      }
    LexPtr--;
    return (AtomExpr*)0;
  }
