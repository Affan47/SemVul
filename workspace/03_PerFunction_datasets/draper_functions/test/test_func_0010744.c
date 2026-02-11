set_sync_cost_prog(char *file_name)
{
    FILE *fp;
    int cores;
    double vpe_cost;
    int ret = 0;
    char buf[COST_FILE_MAX_BUF];

    sync_cost_prog_maxpe = 0;

    if((fp = fopen(file_name, "r")) == NULL) {
        fatal("file open error! \"%s\"",file_name);
    }
    while (fgets(buf, COST_FILE_MAX_BUF, fp) !=NULL) {
        ret = sscanf(buf, "%d %lf", &cores, &vpe_cost);
        if (ret == 2) {
            if(cores > sync_cost_prog_maxpe)
                sync_cost_prog_maxpe = cores;
        }
    }
    fclose(fp);

    if ((sync_cost_prog = calloc(sync_cost_prog_maxpe, sizeof(real)))==NULL)
	fatal("no more room for sync_cost_prog\n");
    if ((fp = fopen(file_name, "r")) == NULL)
        fatal("file open error! \"%s\"",file_name);

    while (fgets(buf, COST_FILE_MAX_BUF, fp) !=NULL) {
        ret = sscanf(buf, "%d %lf", &cores, &vpe_cost);
        if (ret == 2) {
	    sync_cost_prog[cores - 1] = vpe_cost;
	}
    }
    fclose(fp);
#ifdef DEBUG_SYNC_COST_PROG
    print_sync_cost_prog();
    print_sync_cost_prog_complemented();
#endif
    set_sync_cost_complemented();
#ifdef DEBUG_SYNC_COST_PROG
    print_sync_cost_prog();
#endif
}
