plot_dot_map(Agraph_t* gr, int n, int dim, real *x, SparseMatrix polys, SparseMatrix poly_lines, real line_width, char *line_color, real *x_poly, int *polys_groups, char **labels, real *width,
		  float *fsz, float *r, float *g, float *b, char* opacity, char *plot_label, real *bg_color, SparseMatrix A, FILE* f){

  int plot_polyQ = TRUE;
  char *sbuff;
  int len = 0, len_max = 1000;

  sbuff = N_NEW(len_max,char);

  if (!r || !g || !b) plot_polyQ = FALSE;

  if (!gr) {
    fprintf(f, "graph map {\n node [margin = 0 width=0.0001 height=0.00001 shape=plaintext];\n graph [outputorder=edgesfirst, bgcolor=\"#dae2ff\"]\n edge [color=\"#55555515\",fontname=\"Helvetica-Bold\"]\n");
  } else {
    agattr(gr, AGNODE, "margin", "0");
    agattr(gr, AGNODE, "width", "0.0001");
    agattr(gr, AGNODE, "height", "0.0001");
    agattr(gr, AGNODE, "shape", "plaintext");
    agattr(gr, AGNODE, "margin", "0");
    agattr(gr, AGNODE, "fontname", "Helvetica-Bold");
    agattr(gr, AGRAPH, "outputorder", "edgesfirst");
    agattr(gr, AGRAPH, "bgcolor", "#dae2ff");
    if (!A) agattr(gr, AGEDGE, "style","invis");

  }


  if (plot_polyQ) {
    if (!gr) fprintf(f,"_background = \"");
    plot_dot_polygons(&sbuff, &len, &len_max, -1., NULL, polys, x_poly, polys_groups, r, g, b, opacity);
  }


  if (line_width >= 0){
    plot_dot_polygons(&sbuff, &len, &len_max, line_width, line_color, poly_lines, x_poly, polys_groups, NULL, NULL, NULL, NULL);
  }
  if (!gr) {
    fprintf(f,"%s",sbuff);
    fprintf(f,"\"\n");
  } else {
    agattr(gr, AGRAPH, "_background", sbuff);
    agwrite(gr, f);
  }


  if (!gr && labels) plot_dot_labels(f, n, dim, x, labels, width, fsz);

  if (!gr && A) plot_dot_edges(f, A, dim, x);


  if (!gr) fprintf(f, "}\n");


}
