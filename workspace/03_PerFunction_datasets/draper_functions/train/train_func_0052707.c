load_netcdf(rec_start)
     void *rec_start;
{
    int idim;
    int istat=0;
    long coords[H4_MAX_VAR_DIMS];
    long edges[H4_MAX_VAR_DIMS];
    char *charvalp=NULL;
    short *shortvalp=NULL;
    nclong *longvalp=NULL;
    float *floatvalp=NULL;
    double *doublevalp=NULL;


    switch (vars[varnum].type) {
      case NC_CHAR:
      case NC_BYTE:
	charvalp = (char *) rec_start;
	break;
      case NC_SHORT:
	shortvalp = (short *) rec_start;
	break;
      case NC_LONG:
	longvalp = (nclong *) rec_start;
	break;
      case NC_FLOAT:
	floatvalp = (float *) rec_start;
	break;
      case NC_DOUBLE:
	doublevalp = (double *) rec_start;
	break;
      default:
        break;
    }

    if (vars[varnum].dims[0] == rec_dim) {
	coords[0] = netcdf_record_number;
	edges[0] = 1;
    }
    else {
	coords[0] = 0;
	edges[0] = dims[vars[varnum].dims[0]].size;
    }

    for (idim = 1; idim < vars[varnum].ndims; idim++) {
	coords[idim] = 0;
	edges[idim] = dims[vars[varnum].dims[idim]].size;
    }

    switch (vars[varnum].type) {
      case NC_CHAR:
      case NC_BYTE:
	istat = ncvarput (ncid,varnum,coords,edges,(void *)charvalp);
	break;
      case NC_SHORT:
	istat = ncvarput (ncid,varnum,coords,edges,(void *)shortvalp);
	break;
      case NC_LONG:
	istat = ncvarput (ncid,varnum,coords,edges,(void *)longvalp);
	break;
      case NC_FLOAT:
	istat = ncvarput (ncid,varnum,coords,edges,(void *)floatvalp);
	break;
      case NC_DOUBLE:
	istat = ncvarput (ncid,varnum,coords,edges,(void *)doublevalp);
	break;
      default:
        break;
    }
    if (istat == -1)
      derror("error putting value for variable %s",vars[varnum].name);
}
