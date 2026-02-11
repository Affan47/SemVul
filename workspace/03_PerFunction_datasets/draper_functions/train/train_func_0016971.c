Save(const char *filename){

  ofstream output_stream(filename, BINARY_OUT);
  if (!output_stream) fatal_error("PCM::Save -> error creating file.");


  CalcMax();

  char header[100];
  sprintf(header,"PC\n%d %d\n%f\n",width,height,max);
  output_stream.write(header,strlen(header));

    void (*endian_filter)(float *);
    int i4=1;
    char zero_is_little_endian=  * ((static_cast<const char *>((void *) &i4))+3);

    if( zero_is_little_endian == 0)
	endian_filter = (void (*)(float *))do_nothing;
    else
	endian_filter = (void (*)(float *))swap_float_endian;


  pcm_complex *c;
  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++){
      c = Get(x,y);
      if (c) {
	endian_filter(&(c->r));
	endian_filter(&(c->i));
	output_stream.write((const char *)(const void *)&(c->r), sizeof(c->r));
	output_stream.write((const char *)(const void *)&(c->i), sizeof(c->i));
      }
    }
  output_stream.close();
}
