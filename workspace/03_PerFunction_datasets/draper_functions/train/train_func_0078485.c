print_type(Symbol *symp)
{
     if (symp->source)
	  fprintf(outfile, "%s t %s:%d\n",
		  symp->name,
		  symp->source,
		  symp->def_line);
}
