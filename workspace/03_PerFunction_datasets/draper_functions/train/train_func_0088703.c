freeModes(mode* fmodes)
{

    mode * pmodes = (fmodes ? fmodes : modes);


    while (pmodes) {
        mode	 *md = pmodes;

        type_key *mk = md->keys;

        while (mk) {
            type_key* It = mk;
            mk = (type_key*) mk->next;

            freeCmds(getCommand(It));
            It->commands = NULL;

            free(It->key);
            free(It);
        }
        pmodes = (mode*) pmodes->next;

        stringFree(md->name,  BOOL_YES);
	md->name = NULL;
        if (md->parent) {
	    stringFree(md->parent,BOOL_YES);
	    md->parent = NULL;
	}

        free(md);
	md = NULL;
    }

    if (!fmodes) {
        forgetModes();


        freeInternalMode();
    }
}
