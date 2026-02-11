ReadImage( IDirectFBImageProvider_GIF_data *data, int width, int height,
                       u8 cmap[3][MAXCOLORMAPSIZE], u32 key_rgb,
                       bool interlace, bool ignore )
{
     u8 c;
     int v;
     int xpos = 0, ypos = 0, pass = 0;
     u32 *image;


     if (! ReadOK( data->buffer, &c, 1 ))
          GIFERRORMSG("EOF / read error on image data" );

     if (LWZReadByte( data, true, c ) < 0)
          GIFERRORMSG("error reading image" );


     if (ignore) {
          if (verbose)
               GIFERRORMSG("skipping image..." );

          while (LWZReadByte( data, false, c ) >= 0)
               ;
          return NULL;
     }


     if ((image = D_MALLOC(width * height * 4 + 4)) == NULL) {
          GIFERRORMSG("couldn't alloc space for image" );
     }

     if (verbose) {
          GIFERRORMSG("reading %d by %d%s GIF image", width, height,
                      interlace ? " interlaced" : "" );
     }

     while ((v = LWZReadByte( data, false, c )) >= 0 ) {
          u32 *dst = image + (ypos * width + xpos);

          if (v == data->transparent) {
               *dst++ = key_rgb;
          }
          else {
               *dst++ = (0xFF000000              |
                         cmap[CM_RED][v]   << 16 |
                         cmap[CM_GREEN][v] << 8  |
                         cmap[CM_BLUE][v]);
          }

          ++xpos;
          if (xpos == width) {
               xpos = 0;
               if (interlace) {
                    switch (pass) {
                         case 0:
                         case 1:
                              ypos += 8;
                              break;
                         case 2:
                              ypos += 4;
                              break;
                         case 3:
                              ypos += 2;
                              break;
                    }

                    if (ypos >= height) {
                         ++pass;
                         switch (pass) {
                              case 1:
                                   ypos = 4;
                                   break;
                              case 2:
                                   ypos = 2;
                                   break;
                              case 3:
                                   ypos = 1;
                              break;
                              default:
                                   goto fini;
                         }
                    }
               }
               else {
                    ++ypos;
               }
          }
          if (ypos >= height) {
               break;
          }
     }

fini:

     if (LWZReadByte( data, false, c ) >= 0) {
          GIFERRORMSG("too much input data, ignoring extra...");
     }
     return image;
}
