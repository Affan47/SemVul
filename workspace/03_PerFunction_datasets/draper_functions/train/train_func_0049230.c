DoPointers(G_Synset ss)
{
    Pointer p;
    Synonym syn;

    for (p = ss->ptrs; p; p = p->pnext) {

	if (p->status == UNRESOLVED) {


	    if (ss->clusnum &&
		(p->ptype != PERTPTR && p->ptype != ATTRIBUTE &&
		 p->ptype != DERIVATION) &&
		 (p->ptype < CLASSIF_START || p->ptype > CLASSIF_END)) {

		if


		    ((p->phead && p->ptype == ANTPTR &&
		      (syn = FindUniqueSynonym(p, ss, FALSE, ss->clusnum))) ||


		     (p->phead &&
		      (syn = FindUniqueSynonym(p, ss, FALSE, -ss->clusnum))) ||


		     (!p->phead &&
		      (syn = FindUniqueSynonym(p, ss, TRUE, ss->clusnum))))

			ResolveIt(p, syn, ss, FALSE);

	    } else if (syn = FindUniqueSynonym(p, ss, FALSE, 0))
		ResolveIt(p, syn, ss, FALSE);


	    if (p->status == UNRESOLVED) {
		fprintf(logfile, "Unresolved pointer: ");
		if (ss->filenum != p->pfilenum)
		    fprintf(logfile, "%s:", filelist[p->pfilenum].fname);
		fprintf(logfile,
			"%s in file %s, line %d\n",
			PrintPointer(p),
			filelist[ss->filenum].fname,
			ss->lineno);
		errcount++;
	    }
	}
    }
}
