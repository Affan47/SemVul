make_mfg_file(mfgRec *mfg, int nmt, char *mfg_name)
{
    int  i, j;
    FILE *fp;

    if (mfg_name==NULL) {
        fatal("NULL MFG name.\n");
    }
    fp = fopen(mfg_name, "w");
    if (fp ==NULL) {
        fatal("MFG file cannot create!!\n");
    }
    fputs("#%MFG_DATA\n", fp);
    for (i=0 ; i<nmt ; i++) {
        fprintf(fp, "%s%d:", str_block[mfg[i].kind], mfg[i].mtn);
        for (j=0 ; j<mfg[i].npre ; j++) {
            fprintf(fp, " %d*", mfg[i].pre[j]);
        }
        for (j=0 ; j<mfg[i].npred ; j++) {
            fprintf(fp, " %d", mfg[i].pred[j]);
        }
        putc('\n', fp);
    }
    fclose(fp);
}
