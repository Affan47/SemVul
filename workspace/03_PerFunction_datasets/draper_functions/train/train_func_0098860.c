Cblacs_gridmap(int *ConTxt, int *umap, int ldumap, int nprow, int npcol) {
  int i, j, np_me, npall, npwho, myrow, mycol, color, key, rv;
  MPI_Comm comm, newComm, rowComm, colComm;

  if (CblacsGridNew( nprow, npcol, ConTxt, &comm )) {
    CblacsWarn();
    goto gmapErr;
  }

  Cblacs_pinfo( &np_me, &npall );

  myrow = mycol = -1;
  color = MPI_UNDEFINED;
  key = 0;
  for (i = 0; i < nprow; ++i)
    for (j = 0; j < npcol; ++j) {
      npwho = umap[j + i * ldumap];
      if (np_me == npwho) {
        color = 0;
        key = j + i * npcol;
        myrow = i;
        mycol = j;
        goto gmapFound;
      }
    }

  gmapFound:


  rv = MPI_Comm_split( comm, color, key, &newComm );
  if (MPI_SUCCESS != rv) {

    CblacsDeleteCtxt( ConTxt );
    goto gmapErr;
  }
  CblacsSetComm( *ConTxt, newComm );
  if (MPI_COMM_NULL == newComm) {
    CblacsDeleteCtxt( ConTxt );
    return;
  }


  rv = MPI_Comm_split( newComm, myrow, mycol, &rowComm );
  if (MPI_SUCCESS != rv) {
    CblacsDeleteCtxt( ConTxt );
    goto gmapErr;
  }
  CblacsSetRowComm( *ConTxt, rowComm );


  rv = MPI_Comm_split( newComm, mycol, myrow, &colComm );
  if (MPI_SUCCESS != rv) {
    CblacsDeleteCtxt( ConTxt );
    goto gmapErr;
  }
  CblacsSetColComm( *ConTxt, colComm );

  return;

  gmapErr:

  *ConTxt = 0;
  CblacsWarn();
  return;
}
