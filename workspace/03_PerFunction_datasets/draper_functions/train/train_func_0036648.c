noscale(j_decompress_ptr cinfo,
  JDIFFROW diff_buf, JSAMPROW output_buf,
  JDIMENSION width)
{
  unsigned int xindex;
  (void)cinfo;

  for (xindex = 0; xindex < width; xindex++)
    output_buf[xindex] = (JSAMPLE) diff_buf[xindex];
}
