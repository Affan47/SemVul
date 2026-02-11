enter_stage_3_load_tree(PT_main * main,char *tname)
{
    main = main;
    psg.ptmain = PT_init(PT_B_MAX);
    psg.ptmain->stage3 = 1;

    FILE *in;
    long size = GB_size_of_file(tname);
    if (size<0) {
        fprintf(stderr,"PT_SERVER: Error while opening file %s\n",tname);
        exit(EXIT_FAILURE);
    }

    printf ("PT_SERVER: Reading Tree %s of size %li from disk\n",tname,size);
    in = fopen(tname,"r");
    if (!in) {
        fprintf(stderr,"PT_SERVER: Error while opening file %s\n",tname);
        exit(EXIT_FAILURE);
    }
    PTD_read_leafs_from_disk(tname,psg.ptmain,&psg.pt);
    fclose(in);
}
