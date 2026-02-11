repair1(unsigned char *gbuf, long gbufsize)
{
  long i;
  int nerr;
  unsigned char *pds = NULL, *gds = NULL, *bms = NULL, *bds = NULL;

  unsigned char *source;
  size_t sourceLen;
  int bds_len, bds_nbits, bds_flag, lspherc, lcomplex ;
  int bds_head = 11;
  int bds_ext = 0, bds_ubits;
  int datstart = 0;


  nerr = grib1Sections(gbuf, gbufsize, &pds, &gds, &bms, &bds);
  if ( nerr )
    {
      fprintf(stdout, "grib1Sections error\n");
    }


  bds_len   = BDS_Len;
  bds_nbits = BDS_NumBits;
  bds_flag  = BDS_Flag;
  bds_ubits = bds_flag & 15;
  lspherc   =  bds_flag >> 7;
  lcomplex  = (bds_flag >> 6)&1;


  if ( lspherc )
    {
      if ( lcomplex  )
	{
	  int jup, ioff;
	  jup  = bds[15];
	  ioff = (jup+1)*(jup+2);
	  bds_ext = 4 + 3 + 4*ioff;
	}
      else
	{
	  bds_ext = 4;
	}
    }

  datstart = bds_head + bds_ext;

  source = bds + datstart;

  sourceLen = ((((bds_len - datstart)*8-bds_ubits)/bds_nbits)*bds_nbits)/8;

  if ( bds_nbits == 24 )
    {
      long nelem;
      unsigned char *pbuf;
      nelem = sourceLen/3;
      pbuf = (unsigned char *) malloc(sourceLen);
      for ( i = 0; i < nelem; i++ )
	{
	  pbuf[3*i  ] = source[        i];
	  pbuf[3*i+1] = source[  nelem+i];
	  pbuf[3*i+2] = source[2*nelem+i];
	}
      memcpy(source, pbuf, sourceLen);
      free(pbuf);
    }
}
