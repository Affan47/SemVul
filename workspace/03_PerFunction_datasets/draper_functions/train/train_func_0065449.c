PyCMOR_axis(PyObject *self,PyObject *args)
{
  int ierr,axis_id,n=0;
  char *name;
  char *units;
  char *interval;
  int length;
  char type;
  void *coord_vals;
  void *cell_bounds;
  int cell_bounds_ndim;
  char *tmpstr=NULL;
  PyObject *coords_obj,*bounds_obj;
  PyArrayObject *coords=NULL,*bounds=NULL;


  if (!PyArg_ParseTuple(args,"ssiOcOis",&name,&units,&length,&coords_obj,&type,&bounds_obj,&cell_bounds_ndim,&interval))
    return NULL;

  if (coords_obj == Py_None) {
    coord_vals = NULL;
  }
  else {
    coords =(PyArrayObject *) PyArray_ContiguousFromObject(coords_obj,PyArray_NOTYPE,1,0);

    if (coords->nd!=1) {
      printf("ok we need to pass contiguous flattened arrays only!\n");
      return NULL;
    }

    if (type!='c') {
      coord_vals = (void *)coords->data;
      n = cell_bounds_ndim;
    }
    else {
      tmpstr=(char *)malloc(sizeof(char)*length*(cell_bounds_ndim+1));
      for (ierr=0;ierr<length;ierr++) {
	coord_vals = (void *)PyArray_GETPTR1(coords,ierr);
	strncpy(&tmpstr[ierr*(cell_bounds_ndim+1)],coord_vals,cell_bounds_ndim);
	tmpstr[ierr*(cell_bounds_ndim+1)+cell_bounds_ndim]='\0';
      }
      coord_vals=&tmpstr[0];
      n = cell_bounds_ndim + 1;
      for (ierr=0;ierr<length;ierr++) {
      }
    }
  }

  if (bounds_obj == Py_None) {
    cell_bounds = NULL;
  }
  else {
    bounds =(PyArrayObject *) PyArray_ContiguousFromObject(bounds_obj,PyArray_NOTYPE,1,0);
    if (bounds->nd!=1) {
      printf("ok we need to pass contiguous flattened arrays only!\n");
      return NULL;
    }
    cell_bounds = (void *)bounds->data;
  }

  ierr = cmor_axis(&axis_id,name,units,length,coord_vals,type,cell_bounds,n,interval);


  if (coords!=NULL) {Py_DECREF(coords);}
  if (bounds!=NULL) {Py_DECREF(bounds);}

  if (ierr != 0 ) return NULL;

  if (type=='c') {
    free(tmpstr);
  }


  return Py_BuildValue("i",axis_id);
}
