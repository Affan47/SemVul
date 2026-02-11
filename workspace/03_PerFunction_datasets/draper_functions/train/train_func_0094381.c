calc_average() {
  int i = 0, x0, y0, x1, y1;
  struct box *box4;

  JOB->res.numC = 0;
  JOB->res.sumY = 0;
  JOB->res.sumX = 0;
  for_each_data(&(JOB->res.boxlist)) {
    box4 = (struct box *)list_get_current(&(JOB->res.boxlist));
    if( box4->c != PICTURE ){
      x0 = box4->x0;    x1 = box4->x1;
      y0 = box4->y0;    y1 = box4->y1;
      i++;
      if (JOB->res.avX * JOB->res.avY > 0) {
        if (x1 - x0 + 1 > 4 * JOB->res.avX
         && y1 - y0 + 1 > 4 * JOB->res.avY) continue;
        if (4 * (y1 - y0 + 1) < JOB->res.avY || y1 - y0 < 2)
          continue;
      }
      if (x1 - x0 + 1 < 4
       && y1 - y0 + 1 < 6 ) continue;
      JOB->res.sumX += x1 - x0 + 1;
      JOB->res.sumY += y1 - y0 + 1;
      JOB->res.numC++;
    }
  } end_for_each(&(JOB->res.boxlist));
  if ( JOB->res.numC ) {
    JOB->res.avY = (JOB->res.sumY+JOB->res.numC/2) / JOB->res.numC;
    JOB->res.avX = (JOB->res.sumX+JOB->res.numC/2) / JOB->res.numC;
  }
  if (JOB->cfg.verbose){
    fprintf(stderr, "# averages: mXmY= %d %d nC= %d n= %d\n",
  	    JOB->res.avX, JOB->res.avY, JOB->res.numC, i);
  }
  return 0;
}
