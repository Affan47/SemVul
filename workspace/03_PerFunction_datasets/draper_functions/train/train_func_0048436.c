processing_polygon(FILE *f, int np, float *xp, float *yp, real line_width, int fill, int close,
			       float rr, float gg, float bb){
  int i;

  if (np > 0){
    if (fill >= 0){

      fprintf(f, "beginPolygons\ncolor(%f, %f, %f)\n", 255*rr, 255*gg, 255*bb);
    } else {

      fprintf(f, "beginPolylines\n");
      if (line_width > 0){
	fprintf(f, "strokeWeight(%f);\n", line_width);
      }
    }
    for (i = 0; i < np; i++){

      fprintf(f, "%f %f\n",xp[i], yp[i]);
    }

    if (fill >= 0){
      fprintf(f, "endPolygons\n");
    } else {
      fprintf(f, "endPolylines\n");
    }

  }
}
