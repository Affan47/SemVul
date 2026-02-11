setup()
{
  int i,j,k,m,n;
  double rtmp;


  memory->destroy(elem2param);
  memory->create(elem2param,nelements,nelements,nelements,"pair:elem2param");

  for (i = 0; i < nelements; i++)
    for (j = 0; j < nelements; j++)
      for (k = 0; k < nelements; k++) {
	n = -1;
	for (m = 0; m < nparams; m++) {
	  if (i == params[m].ielement && j == params[m].jelement &&
	      k == params[m].kelement) {
	    if (n >= 0) error->all(FLERR,"Potential file has duplicate entry");
	    n = m;
	  }
	}

	elem2param[i][j][k] = n;
      }


  for (m = 0; m < nparams; m++) {

    params[m].cut = params[m].cutoff;
    params[m].cutsq = params[m].cut * params[m].cut;

    params[m].theta0 = params[m].theta0 / 180.0 * PI;

  }


  cutmax = 0.0;
  for (m = 0; m < nparams; m++) {
    rtmp = sqrt(params[m].cutsq);
    if (rtmp > cutmax) cutmax = rtmp;
  }
}
