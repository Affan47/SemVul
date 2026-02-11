Cudd_zddCoverPathToString(
  DdManager *zdd		,
  int *path			,
  char *str
  )
{
    int nvars = zdd->sizeZ;
    int i;
    char *res;

    if (nvars & 1) return(NULL);
    nvars >>= 1;
    if (str == NULL) {
	res = ALLOC(char, nvars+1);
	if (res == NULL) return(NULL);
    } else {
	res = str;
    }
    for (i = 0; i < nvars; i++) {
	int v = (path[2*i] << 2) | path[2*i+1];
	switch (v) {
	case 0:
	case 2:
	case 8:
	case 10:
	    res[i] = '-';
	    break;
	case 1:
	case 9:
	    res[i] = '0';
	    break;
	case 4:
	case 6:
	    res[i] = '1';
	    break;
	default:
	    res[i] = '?';
	}
    }
    res[nvars] = 0;

    return(res);

}
