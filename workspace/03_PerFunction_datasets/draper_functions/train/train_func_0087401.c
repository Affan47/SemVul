vtinit(void)
{
    int i, j;
    VIDEO *vp;
    CELL   ac;

    ac.c = ' ';
    ac.a = 0;

    if(Pmaster == NULL)
      vtterminalinfo(gmode & MDTCAPWINS);

    (*term.t_open)();

    (*term.t_rev)(FALSE);
    vscreen = (VIDEO **) malloc((term.t_nrow+1)*sizeof(VIDEO *));
    memset(vscreen, 0, (term.t_nrow+1)*sizeof(VIDEO *));
    if (vscreen == NULL){
	emlwrite("Allocating memory for virtual display failed.", NULL);
        return(FALSE);
    }

    pscreen = (VIDEO **) malloc((term.t_nrow+1)*sizeof(VIDEO *));
    memset(pscreen, 0, (term.t_nrow+1)*sizeof(VIDEO *));
    if (pscreen == NULL){
	free((void *)vscreen);
	emlwrite("Allocating memory for physical display failed.", NULL);
        return(FALSE);
    }


    for (i = 0; i <= term.t_nrow; ++i) {
        vp = (VIDEO *) malloc(sizeof(VIDEO)+(term.t_ncol*sizeof(CELL)));

        if (vp == NULL){
	    free((void *)vscreen);
	    free((void *)pscreen);
	    emlwrite("Allocating memory for virtual display lines failed.",
		     NULL);
            return(FALSE);
	}
	else
	  for(j = 0; j < term.t_ncol; j++)
	    vp->v_text[j] = ac;

	vp->v_flag = 0;
        vscreen[i] = vp;

        vp = (VIDEO *) malloc(sizeof(VIDEO)+(term.t_ncol*sizeof(CELL)));

        if (vp == NULL){
            free((void *)vscreen[i]);
	    while(--i >= 0){
		free((void *)vscreen[i]);
		free((void *)pscreen[i]);
	    }

	    free((void *)vscreen);
	    free((void *)pscreen);
	    emlwrite("Allocating memory for physical display lines failed.",
		     NULL);
            return(FALSE);
	}
	else
	  for(j = 0; j < term.t_ncol; j++)
	    vp->v_text[j] = ac;

	vp->v_flag = 0;
        pscreen[i] = vp;
    }

    return(TRUE);
}
