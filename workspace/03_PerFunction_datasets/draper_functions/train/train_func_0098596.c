__to_dispst_str(char *s, word32 st)
{
 switch ((byte) st) {
  case ST_HIGHZ: strcpy(s, "Hi"); break;
  case ST_SMALL: strcpy(s, "Sm"); break;
  case ST_MEDIUM: strcpy(s, "Me"); break;
  case ST_WEAK: strcpy(s, "We"); break;
  case ST_LARGE: strcpy(s, "La"); break;
  case ST_PULL: strcpy(s, "Pu"); break;
  case ST_STRONG: strcpy(s, "St"); break;
  case ST_SUPPLY: strcpy(s, "Su"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}
