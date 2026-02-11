dump_layout(char **layout, RMParms *RP) {
    int i, j;

    for (i = 0; i < RP->Xsize; i++) {
        for (j = 0; j < RP->Ysize; j++) {
            if (layout[i][j] == 0)
                layout[i][j] = ' ';
            printf("%c", layout[i][j]);
            if (layout[i][j] == ' ')
                layout[i][j] = 0;
        }
        printf("\n");
    }
    printf("\n");
}
