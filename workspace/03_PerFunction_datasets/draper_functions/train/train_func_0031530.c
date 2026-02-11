print_usage (const char *prg_name)
{
     int i = 0;

     fprintf (stderr, "\nDirectFB Glyph Image File Format Tool (version %s)\n\n", DIRECTFB_VERSION);
     fprintf (stderr, "Usage: %s [options]\n\n", prg_name);
     fprintf (stderr, "Options:\n");
     fprintf (stderr, "   -f, --format    <pixelformat>   Choose the pixel format (default A8)\n");
     fprintf (stderr, "   -s, --sizes     <s1>[,s2...]    Choose sizes to generate glyph images for\n");
     fprintf (stderr, "   -h, --help                      Show this help message\n");
     fprintf (stderr, "   -v, --version                   Print version information\n");
     fprintf (stderr, "\n");

     fprintf (stderr, "Known pixel formats with alpha:\n");

     while (format_names[i].format != DSPF_UNKNOWN) {
          DFBSurfacePixelFormat format = format_names[i].format;

          if (DFB_PIXELFORMAT_HAS_ALPHA(format)) {
               fprintf (stderr, "   %-10s %2d bits, %d bytes",
                        format_names[i].name, DFB_BITS_PER_PIXEL(format),
                        DFB_BYTES_PER_PIXEL(format));

               if (DFB_PIXELFORMAT_IS_INDEXED(format))
                    fprintf (stderr, "   INDEXED");

               if (DFB_PLANAR_PIXELFORMAT(format)) {
                    int planes = DFB_PLANE_MULTIPLY(format, 1000);

                    fprintf (stderr, "   PLANAR (x%d.%03d)",
                             planes / 1000, planes % 1000);
               }

               fprintf (stderr, "\n");
          }

          ++i;
     }
     fprintf (stderr, "\n");
}
