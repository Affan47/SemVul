macke_to_embl(inf, outf)
     char       *inf, *outf;
{
    FILE            *IFP1, *IFP2, *IFP3, *ofp;
    FILE_BUFFER  ifp1, ifp2, ifp3;
    char             temp[TOKENNUM];

    if ((IFP1=fopen(inf, "r"))==NULL ||
        (IFP2=fopen(inf, "r"))==NULL ||
        (IFP3=fopen(inf, "r"))==NULL)
    {
        sprintf(temp, "Cannot open input file %s\n", inf);
        error(99, temp);
    }

    ifp1 = create_FILE_BUFFER(inf, IFP1);
    ifp2 = create_FILE_BUFFER(inf, IFP2);
    ifp3 = create_FILE_BUFFER(inf, IFP3);

    if(Lenstr(outf)<=0) ofp = stdout;
    else if((ofp=fopen(outf, "w"))==NULL)       {
        sprintf(temp, "Cannot open output file %s\n", outf);
        error(43, temp);
    }
    init();
    init_seq_data();
    init_genbank();
    init_macke();
    init_embl();

#ifdef log
    fprintf(stderr, "Start converting...\n");
#endif

    while(macke_in(ifp1, ifp2, ifp3)!=EOF)      {

        data.numofseq++;


        if(mtog()&&gtoe()&&partial_mtoe()) embl_out(ofp);
        else error(14,
                   "Conversion from macke to embl fails, Exit");

        init_genbank();
        init_embl();
        init_macke();

#ifdef log
        if((data.numofseq % 50)==0)
            fprintf(stderr, "%d sequences are converted...\n",
                    data.numofseq);
#endif

    }

#ifdef log
    fprintf(stderr,
            "Total %d sequences have been processed\n", data.numofseq);
#endif

}
