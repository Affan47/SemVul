read_edge(int richcount, double atts[], double **edge)
{
    FILE *fp;
    register int i, j;
    float tmp;


    fp = fopen3("r.le.para/edge", "r");


    for (i = 0; i < richcount; i++) {
	fscanf(fp, "%f", &tmp);
	atts[i] = tmp;
    }
    while (fgetc(fp) != '\n')
	if (fgetc(fp) != ' ') {
	    fprintf(stdout, "\n");
	    fprintf(stdout,
		    "   *************************************************\n");
	    fprintf(stdout,
		    "    The edge file (r.le.para/edge) is incorrect     \n");
	    fprintf(stdout,
		    "       since more/less than the %d attributes found \n",
		    richcount);
	    fprintf(stdout,
		    "       in the map are listed in the edge file       \n");
	    fprintf(stdout,
		    "   *************************************************\n");
	    exit(1);
	}


    for (i = 0; i < richcount; i++) {
	fscanf(fp, "%f", &tmp);
	for (j = 0; j < i; j++) {
	    edge[i][j] = edge[j][i];
	}
	for (j = 0; j < richcount; j++) {
	    fscanf(fp, "%f", &tmp);
	    edge[i][j] = tmp;
	}
	while (fgetc(fp) != '\n') ;
    }
    fclose(fp);

    return;
}
