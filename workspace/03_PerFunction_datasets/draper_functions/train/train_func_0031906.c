_dxf_ExPrintProgramIO(Program *p)
{
    int i, j, index;
    gfunc *gf;

    printf("%d Functions:\n", SIZE_LIST(p->funcs));
    for (i = 0; i < SIZE_LIST(p->funcs); ++i)
    {
	gf = FETCH_LIST(p->funcs, i);
	printf("%c%c %3d: %s: in: ",
	  p->cursor+1 == i? '>': ' ',
	  p->first_skipped != -1 && p->first_skipped == i? '*': ' ',
	  i, _dxf_ExGFuncPathToString(gf));
        for (j = 0; j < SIZE_LIST(gf->inputs); ++j) {
            index = *FETCH_LIST(gf->inputs, j);
            if(index != -1) printf("%d ", index);
        }
        printf(" out: ");
        for (j = 0; j < SIZE_LIST(gf->outputs); ++j) {
            index = *FETCH_LIST(gf->outputs, j);
            if(index != -1) printf("%d ", index);
        }
        printf("\n");
        if(gf->ftype == F_MACRO && gf->func.subP) {
            printf("macro %s ", gf->name);
            _dxf_ExPrintProgramIO(gf->func.subP);
        }
    }
    return (0);
}
