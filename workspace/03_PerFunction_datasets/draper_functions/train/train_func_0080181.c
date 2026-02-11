_encodepart(oggpack_buffer *opb,float *vec, int n,
		       codebook *book,long *acc){
  int i,bits=0;
  int dim=book->dim;
  int step=n/dim;

  for(i=0;i<step;i++){
    int entry=local_book_besterror(book,vec+i*dim);

#ifdef TRAIN_RES
    if(entry>0)
      acc[entry]++;
#endif

    bits+=vorbis_book_encode(book,entry,opb);

  }

  return(bits);
}
