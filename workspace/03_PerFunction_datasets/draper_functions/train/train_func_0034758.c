piped_sout (void *stream, char *s, long unsigned int size)
{
    int i, o;

    if(S(stream)->out.d < 0)
      return(0L);

    if((i = (int) size) != 0){
	while((o = write(S(stream)->out.d, s, i)) != i)
	  if(o < 0){
	      if(errno != EINTR){
		  piped_abort(stream);
		  return(0L);
	      }
	  }
	  else{
	      s += o;
	      i -= o;
	  }
    }

    return(1L);
}
