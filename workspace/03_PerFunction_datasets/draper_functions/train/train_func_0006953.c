print_var_type(FILE *fd, const Lsymtab *symt)
#else
print_var_type(fd,symt)
#endif

#if HAVE_STDC
#else
     FILE *fd;
     Lsymtab *symt;
#endif
{
  int adjustable=0;
  int t = get_type(symt);
  int s = get_size(symt,t);

	  (void)fprintf(fd," %4s",type_name[t]);


	  if( s != size_DEFAULT ) {
	    if(t != type_STRING || s > 1)
	      (void)fprintf(fd,"%d",s);
	    else
	      if(s == size_ADJUSTABLE) {
		adjustable++;
		(void)fprintf(fd,"+");
	      }
	      else
		(void)fprintf(fd," ");
	  }
  return adjustable;
}
