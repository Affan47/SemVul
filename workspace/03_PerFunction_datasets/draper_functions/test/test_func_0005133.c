genbank_to_macke(inf, outf)
     char   *inf, *outf;
{
    FILE        *IFP, *ofp;
    FILE_BUFFER  ifp;
    char         temp[TOKENNUM];
    int          indi, total_num;

    if((IFP=fopen(inf, "r"))==NULL) {
        sprintf(temp, "CANNOT open input file %s, exit.\n", inf);
        error(0, temp);
    }
    ifp              = create_FILE_BUFFER(inf, IFP);
    if(Lenstr(outf) <= 0)   ofp = stdout;
    else if((ofp=fopen(outf, "w"))==NULL)   {
        sprintf(temp, "CANNOT open output file %s, exit.\n", outf);
        error(1, temp);
    }

    init();
    init_gm_data();
    macke_out_header(ofp);

#ifdef log
    fprintf(stderr, "Start converting...\n");
#endif

    for(indi=0; indi<3; indi++) {
        FILE_BUFFER_rewind(ifp);
        init_seq_data();
        while(genbank_in(ifp)!=EOF) {
            data.numofseq++;
            if(gtom()) {

                switch(indi)    {
                    case 0:

                        macke_out0(ofp, GENBANK);
                        break;
                    case 1:

                        macke_out1(ofp);
                        break;
                    case 2:

                        macke_out2(ofp);
                        break;
                    default: ;
                }
            } else error(7,
                         "Conversion from genbank to macke fails, Exit");
            init_gm_data();
#ifdef log
            if((data.numofseq % 100)==0)
                fprintf(stderr, "%d sequences have been processed\n",
                        data.numofseq);
#endif
        }
        total_num = data.numofseq;
        if(indi==0) {
            fprintf(ofp, "#-\n");

            warning_out = 0;
        }
    }

    warning_out = 1;

#ifdef log
    fprintf(stderr,
            "Total %d sequences have been processed\n", total_num);
#endif

}
