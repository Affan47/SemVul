showtext3c( const char *       txt,
                       int         xpos,
                       int         ypos)
{


    int         i, j,k;
    int         newx = 0;
    int          cnt;
    int         orgjus;


   npush( activefontsettings );
   char s2[1000];
   char s[1000];
   char s3[1000];
   s2[0] = 0;

   i = 0;
   cnt = 0;
   while ( txt[i] ) {
      if (txt[i] != '~') {
         s2[cnt] = txt[i];
         cnt++;
         s2[cnt] = 0;
      }
      i++;
   }

   cnt = -2;
   showtext2c(s2,xpos,ypos);
   i = 0;
   orgjus = activefontsettings.justify;

   while ((txt[i] != '~') && (txt[i] ))
      i++;

   while ( txt[i] ) {
      cnt+=2;

      j = i + 1;
      s[0] = 0;
      s3[0] = 0;
      k=0;
      activefontsettings.background = 255;

      while ((txt[j] != '~') && ( txt[j] != 0)) {
         s[k] = txt[j];
         k++;
         s[k] = 0;
         j++;
      }

      if (s[0] != 0) {
         strncpy( s3, s2, k+i-cnt );
         s3[k+i-cnt]=0;
         if (orgjus == lefttext) {
            newx = xpos + gettextwdth(s3, NULL) - gettextwdth(s,NULL);
         }
         else
            if (orgjus == centertext) {
               newx = xpos + (activefontsettings.length - gettextwdth(s2, NULL)) / 2 + gettextwdth(s3,NULL) - gettextwdth(s,NULL) + 1;
            }
            else
               if (orgjus == righttext) {
                  newx = xpos + 1 + (activefontsettings.length - gettextwdth(s2, NULL)) + gettextwdth(s3,NULL) - gettextwdth(s,NULL);
               }
         activefontsettings.font = activefontsettings.markfont;
         activefontsettings.justify = lefttext;
         showtext2c(s,newx,ypos);
      }
      i = j + 1;
      while ((txt[i] != '~') && (txt[i] != 0))
        i++;
   }

   npop( activefontsettings );
}
