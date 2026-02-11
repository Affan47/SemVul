eldeststree(trp)
syntaxtree *trp;
{
	syntaxtree *tmptr;

	while (trp) {
		tmptr = getparent(trp);
		if (!(trp -> flags & ST_NEXT)) return(tmptr);
		trp = tmptr;
	}

	return(NULL);
}
