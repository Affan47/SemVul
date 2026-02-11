min4_dispatch()


{
    int startingsize,nbtot,nbop,hint;
    triangle nft[MAXN];

    if (minimumdeg <= 0) minimumdeg = 4;
    if (minconnec <= 0) minconnec = 3;
    startingsize = 6;

    CHECKRANGE(maxnv,"n",startingsize,MAXN);
    CHECKRANGE(minconnec,"-c",3,4);
    CHECKRANGE(minimumdeg,"-m",4,4);

    INCOMPAT(tswitch,"-m4 or -c4","-t");
    INCOMPAT(qswitch,"-m4 or -c4","-q");
    INCOMPAT(edgebound[0]>=0,"-m4 without -p","-e");
    INCOMPAT(maxfacesize>=0,"-m4 without -p","-f");

    if (dswitch) strcpy(outtypename,"cubic graphs");
    else         strcpy(outtypename,"triangulations");

    open_output_file();

    needgroup = Gswitch;
    if (minconnec == 4) xswitch = TRUE;

    xconnec = minconnec;

    hint = MIN(maxnv <= 19 ? maxnv-4 : maxnv-5, 17);
    initialize_splitting(startingsize,hint,maxnv-3);
    if (splitlevel == 0 && res > 0) return;

    initialize_min4();
    canon(degree,numbering,&nbtot,&nbop);

    if (xswitch || minconnec == 4)
	scanmin4c(nbtot,nbop,splitlevel==6,NULL,nft,0);
    else
	scanmin4(nbtot,nbop,splitlevel==6,NULL);
}
