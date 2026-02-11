fortranMangle(char *orig, char *mangled)
{
  int uscore, i;

  strcpy( mangled, orig );
  if(ELMER_LINKTYP == 1 || ELMER_LINKTYP == 3 || ELMER_LINKTYP == 4)
  {
    for( i=0 ; i<strlen(mangled) ; i++ )
    {
      if ( mangled[i] >= 'A'  && mangled[i] <= 'Z' )
	mangled[i] += 'a' - 'A';
    }
  }
  if(ELMER_LINKTYP == 2)
  {
    for( i=0; i<strlen(mangled); i++ )
    {
      if ( mangled[i] >= 'a'  && mangled[i] <= 'z' )
	mangled[i] += 'A' - 'a';
    }
  }

  if(ELMER_LINKTYP == 1)
  {
      strcat( mangled, "_" );
  }
  else if(ELMER_LINKTYP == 4)
  {
    uscore = 0;
    for( i=0; i<strlen(mangled); i++ )
      if(mangled[i] == '_')
	uscore++;

    if(uscore == 0)
    {
      strcat( mangled, "_" );
    }
    else
    {
      strcat( mangled, "__" );
    }
  }
}
