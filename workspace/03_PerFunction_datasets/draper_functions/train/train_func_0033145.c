generate_code()
{
  if ( putexpr != NULL ) {
    if (putexpr->islvalue())
      fprintf(codefile,"%s.print();\n", putexpr->generate_code() );
    else
      fprintf(codefile,"cout << ( %s );\n", putexpr->generate_code() );
  }
  else {
    fprintf(codefile,"cout << \"%s\";\n", putstring);
  }
  return "ERROR!";
}
