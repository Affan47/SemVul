write_pgm_image_int(image_int image, char * name)
{
  FILE * f;
  unsigned int x,y,n;
  int v,max,min;


  max = min = 0;
  for(y=0; y<image->ysize; y++)
    for(x=0; x<image->xsize; x++)
      {
        v = image->data[ x + y * image->xsize ];
        if( v > max ) max = v;
        if( v < min ) min = v;
      }
  if( min < 0 ) fprintf(stderr,
        "Warning: write_pgm_image_int: negative values in '%s'.\n",name);
  if( max > 65535 ) fprintf(stderr,
        "Warning: write_pgm_image_int: values exceeding 65535 in '%s'.\n",name);


  if( strcmp(name,"-") == 0 ) f = stdout;
  else f = fopen(name,"w");
  if( f == NULL ) error("unable to open output image file %s", name);


  fprintf(f,"P2\n");
  fprintf(f,"%u %u\n",image->xsize,image->ysize);
  fprintf(f,"%d\n",max);


  for(n=0,y=0; y<image->ysize; y++)
    for(x=0; x<image->xsize; x++)
      {
        fprintf(f,"%d ",image->data[ x + y * image->xsize ]);
        if(++n==8)
          {
            fprintf(f,"\n");
            n = 0;
          }
      }


  if( f != stdout && fclose(f) == EOF )
      error("unable to close file %s while writing PGM file.", name);
}
