fmfr_print( FMField *obj, FILE *file, int32 mode )
{
  int32 i, j, il;

  if (mode == 0) {
    fprintf( file, "%d %d %d %d %d\n", obj->nLev, obj->nRow, obj->nCol,
	     obj->offset, obj->nColFull );
    for (il = 0; il < obj->nLev; il++) {
      fprintf( file, "%d\n", il );
      for (i = 0; i < obj->nRow; i++) {
	for (j = 0; j < obj->nCol; j++) {
	  fprintf( file, " %.12e",
		   obj->val[obj->offset+obj->nColFull*(obj->nRow*il+i)+j] );
	}
	fprintf( file, "\n" );
      }
    }
  } else if (mode == 1) {
    fmf_print( obj, file, mode );
  } else {
    errput( ErrHead "ERR_Switch!\n" );
  }

  return( RET_OK );
}
