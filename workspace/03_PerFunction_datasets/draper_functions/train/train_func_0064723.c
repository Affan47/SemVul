__glxGetMscRate(struct glx_screen *psc,
		int32_t * numerator, int32_t * denominator)
{
#ifdef XF86VIDMODE
   XF86VidModeModeLine mode_line;
   int dot_clock;
   int i;

   if (XF86VidModeQueryVersion(psc->dpy, &i, &i) &&
       XF86VidModeGetModeLine(psc->dpy, psc->scr, &dot_clock, &mode_line)) {
      unsigned n = dot_clock * 1000;
      unsigned d = mode_line.vtotal * mode_line.htotal;

# define V_INTERLACE 0x010
# define V_DBLSCAN   0x020

      if (mode_line.flags & V_INTERLACE)
         n *= 2;
      else if (mode_line.flags & V_DBLSCAN)
         d *= 2;


      if (n % d == 0) {
         n /= d;
         d = 1;
      }
      else {
         static const unsigned f[] = { 13, 11, 7, 5, 3, 2, 0 };


         for (i = 0; f[i] != 0; i++) {
            while (n % f[i] == 0 && d % f[i] == 0) {
               d /= f[i];
               n /= f[i];
            }
         }
      }

      *numerator = n;
      *denominator = d;

      return True;
   }
   else
#endif

   return False;
}
