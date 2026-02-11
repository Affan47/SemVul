Affiche()
{
    printf("%lu : \n", (long unsigned int) bords.size());
    for (int i = 0; i < int(bords.size()); i++) {
        printf("(%f %f %f %i) ",bords[i].pos,bords[i].val,bords[i].pente,(bords[i].start?1:0));
    }

    printf("\n");
    printf("%lu : \n", (long unsigned int) runs.size());

    for (int i = 0; i < int(runs.size()); i++) {
        printf("(%f %f -> %f %f / %f)",
               runs[i].st, runs[i].vst, runs[i].en, runs[i].ven, runs[i].pente);
    }

    printf("\n");
}
