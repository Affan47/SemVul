doorify_layout(char **maze, RMParms *RP) {
    int ndoors = RP->Xsize*RP->Ysize/60;
    int *doorlist_x;
    int *doorlist_y;
    int doorlocs = 0;
    int i, j;

    doorlist_x = malloc(sizeof(int)*RP->Xsize*RP->Ysize);
    doorlist_y = malloc(sizeof(int)*RP->Xsize*RP->Ysize);


    for (i = 1; i < RP->Xsize-1; i++)
        for (j = 1; j < RP->Ysize-1; j++) {
            int sindex = surround_flag(maze, i, j, RP);
            if (sindex == 3 || sindex == 12) {

                doorlist_x[doorlocs] = i;
                doorlist_y[doorlocs] = j;
                doorlocs++;
            }
        }

    while (ndoors > 0 && doorlocs > 0) {
        int di;
        int sindex;

        di = RANDOM()%doorlocs;
        i = doorlist_x[di];
        j = doorlist_y[di];
        sindex = surround_flag(maze, i, j, RP);
        if (sindex == 3 || sindex == 12) {
            maze[i][j] = 'D';
            ndoors--;
        }

        doorlocs--;
        doorlist_x[di] = doorlist_x[doorlocs];
        doorlist_y[di] = doorlist_y[doorlocs];
    }
    free(doorlist_x);
    free(doorlist_y);
}
