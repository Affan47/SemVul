read_pgm_image_double(char * name)
{
  FILE * f;
  int c,bin=FALSE;
  unsigned int xsize,ysize,depth,x,y;
  image_double image;


  if( strcmp(name,"-") == 0 ) f = stdin;
  else
	  f = fopen(name,"rb");
  if( f == NULL )
	  error("unable to open input image file %s", name);


  if( getc(f) != 'P' ) error("not a PGM file!");
  if( (c=getc(f)) == '2' ) bin = FALSE;
  else if( c == '5' ) bin = TRUE;
  else error("not a PGM file!");
  skip_whites_and_comments(f);
  xsize = get_num(f);
  skip_whites_and_comments(f);
  ysize = get_num(f);
  skip_whites_and_comments(f);
  depth = get_num(f);
  if(depth==0) fprintf(stderr,"Warning: depth=0, probably invalid PGM file\n");

  if(!isspace(c=getc(f))) error("corrupted PGM file.");


  image = new_image_double(xsize,ysize);


  for(y=0;y<ysize;y++)
    for(x=0;x<xsize;x++)
      image->data[ x + y * xsize ] = bin ? (double) getc(f)
                                         : (double) get_num(f);


  if( f != stdin && fclose(f) == EOF )
      error("unable to close file %s while reading PGM file.", name);

  return image;
}
