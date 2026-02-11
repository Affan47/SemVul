setLogColor(const unsigned int color)
{
   if(gColorMode) {
      fprintf(stdlog,"\x1b[%dm",
              30 + (color % 8) + ((color > 8) ? 60 : 0));
   }
}
