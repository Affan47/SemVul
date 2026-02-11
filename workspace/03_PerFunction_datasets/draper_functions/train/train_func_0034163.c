lconvert( lstring )
  char *lstring;
{


   double lval;
   char *pfix;

   lval = strtod((const char *)lstring, &pfix);

   while (*pfix != '\0' && isspace(*pfix)) pfix++;


   switch (*pfix) {
      case 'n': case 'N': lval *= 0.1;   break;
      case 'u': case 'U': lval *= 100;   break;
      case 'm': case 'M': lval *= 1.0e5; break;
      case '\0': case 'l': lval *= LAMBDACM; break;
      default:
	 rsimerror( simfname, lineno,
	    "Unknown length measure suffix %s, assuming lambda\n", pfix);
	 break;
   }
   return (float)lval;
}
