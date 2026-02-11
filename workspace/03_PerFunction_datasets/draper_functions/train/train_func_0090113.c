fmlbp_print_page(gx_device_printer *pdev, FILE *prn_stream)
{
  int line_size = gdev_mem_bytes_per_scan_line((gx_device *)pdev);
#ifdef	FMLBP_NOPAPERSIZE
  char data[LINE_SIZE*2];
#else
  char paper[16];
  byte *data = (byte *)gs_malloc(pdev->memory->non_gc_memory, 1, line_size, "fmlpr_print_page(data)");
  if(data == NULL) return_error(gs_error_VMerror);
#endif


  fwrite(can_inits, sizeof(can_inits), 1, prn_stream);
  fprintf(prn_stream, "%c%c%d!I", PU1, 0);
#ifndef	OLD_FMLBP_400DPI
  fprintf(prn_stream, "%c%c%d!A", PU1,
          (int)(pdev->x_pixels_per_inch));
#endif
#ifndef	FMLBP_NOPAPERSIZE
  fprintf(prn_stream, "%c%c%s!F", PU1,
          gdev_fmlbp_paper_size(pdev, paper));
#endif


  {	int lnum;
        byte rmask = (byte)(0xff << (-pdev->width & 7));

        for ( lnum = 0; lnum < pdev->height; lnum++ )
          {	byte *end_data = data + line_size;
                int s = gdev_prn_copy_scan_lines(pdev, lnum,
                                                (byte *)data, line_size);
                if(s < 0) return_error(s);

                end_data[-1] &= rmask;

                while ( end_data > data && end_data[-1] == 0 )
                  end_data--;
                if ( end_data != data ) {
                  int num_cols = 0;
                  int out_count = 0;
                  byte *out_data = data;

                  while(out_data < end_data && *out_data == 0) {
                    num_cols += 8;
                    out_data++;
                  }
                  out_count = end_data - out_data;


                  goto_xy(prn_stream, num_cols, lnum);


                  fprintf(prn_stream, "%c%c%d;%d;0!a",
                          PU1, out_count, out_count*8 );


                  fwrite(out_data, sizeof(byte), out_count, prn_stream);
                }
              }
      }

  fputc(0x0c,prn_stream);
  fflush(prn_stream);
#ifndef	FMLBP_NOPAPERSIZE
  gs_free(pdev->memory->non_gc_memory, (char *)data, line_size, sizeof(byte), "fmlbp_print_page(data)");
#endif

  return 0;
}
