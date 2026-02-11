ccr_print_page(gx_device_printer *pdev, FILE *pstream)
{
  cmyrow *linebuf;
  int line_size = gdev_prn_raster((gx_device *)pdev);
  int pixnum = pdev->width;
  int lnum = pdev->height;
  int l, p, b;
  int cmy, c, m, y;
  byte *in;
  byte *data;

  if((in = (byte *)gs_malloc(pdev->memory, line_size, 1, "gsline")) == NULL)
     return_error(gs_error_VMerror);

  if(alloc_rb( pdev->memory, &linebuf, lnum))
    {
      gs_free(pdev->memory, in, line_size, 1, "gsline");
      return_error(gs_error_VMerror);
    }

  for ( l = 0; l < lnum; l++ )
     {	gdev_prn_get_bits(pdev, l, in, &data);
        if(alloc_line(pdev->memory, &linebuf[l], pixnum))
          {
            gs_free(pdev->memory, in, line_size, 1, "gsline");
            free_rb_line( pdev->memory, linebuf, lnum, pixnum );
            return_error(gs_error_VMerror);
          }
        for ( p=0; p< pixnum; p+=8)
          {
            c=m=y=0;
            for(b=0; b<8; b++)
            {
              c <<= 1; m <<= 1; y <<= 1;
              if(p+b < pixnum)
                cmy = *data;
              else
                cmy = 0;

              c |= cmy>>2;
              m |= (cmy>>1) & 0x1;
              y |= cmy & 0x1;
              data++;
            }
            add_cmy8(&linebuf[l], c, m, y);
          }
      }
CCFILESTART(pstream);
write_cpass(linebuf, lnum, YPASS, pstream);
CCNEWPASS(pstream);
write_cpass(linebuf, lnum, MPASS, pstream);
CCNEWPASS(pstream);
write_cpass(linebuf, lnum, CPASS, pstream);
CCFILEEND(pstream);


gs_free(pdev->memory, in, line_size, 1, "gsline");
free_rb_line( pdev->memory, linebuf, lnum, pixnum );
return 0;
}
