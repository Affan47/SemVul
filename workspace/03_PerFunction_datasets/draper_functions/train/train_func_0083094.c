get_side_type(char *type, enum CBLAS_SIDE *side) {
  if( (strncmp( type,"l",1 )==0)||(strncmp( type,"L",1 )==0) )
        *side = CblasLeft;
  else if( (strncmp( type,"r",1 )==0)||(strncmp( type,"R",1 )==0) )
        *side = CblasRight;
  else *side = UNDEFINED;
}
