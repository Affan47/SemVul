read_workout ( char *filename, S710_Filter filter, S710_HRM_Type type )
{
  int            fd;
  struct stat    sb;
  workout_t *    w = NULL;
  unsigned char  buf[65536];

  if ( stat(filename,&sb) != -1 ) {
    if ( (fd = open(filename,O_RDONLY)) != -1 ) {
      if ( sb.st_size < (int)sizeof(buf) ) {
	if ( read(fd,buf,sb.st_size) == sb.st_size ) {
	  if ( buf[0] + (buf[1]<<8) == sb.st_size ) {


	    if ( type == S710_HRM_AUTO ) {
	      type = detect_hrm_type(buf,sb.st_size);
	    }


	    if ( type != S710_HRM_UNKNOWN ) {
	      w = extract_workout(buf,filter,type);
	    } else {
	      fprintf(stderr,"%s: unable to auto-detect HRM type\n",
		      filename);
	    }
	  } else {
	    fprintf(stderr,"%s: invalid data [%d] [%d] (size %ld)\n",
		    filename,buf[0],buf[1],(long)sb.st_size);
	  }
	} else {
	  fprintf(stderr,"%s: read(%ld): %s\n",
		  filename,(long)sb.st_size,strerror(errno));
	}
      } else {
	fprintf(stderr,"%s: file size of %ld bytes is too big!\n",
		filename,(long)sb.st_size);
      }
      close(fd);
    } else {
      fprintf(stderr,"open(%s): %s\n",filename,strerror(errno));
    }
  } else {
    fprintf(stderr,"stat(%s): %s\n",filename,strerror(errno));
  }

  return w;
}
