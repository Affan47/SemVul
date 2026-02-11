view_logo(outname)
char *outname;
{
   char       PSviewer[MAXNAME], PSviewer_opt[MAXNAME] ;
   char       PSprint[MAXNAME], ans[2] , line[80] ;

   strcpy(PSviewer, "pageview") ;
   strcpy(PSviewer_opt, "-left") ;
   strcpy(PSprint, "lpr") ;
   ans[0] = 'V' ;

   while (toupper(ans[0]) == 'V')
      {
      printf("\nThe created sequence-logo file (%s) is a PostScript file.\n",
	     outname) ;
      printf("  (V to view logo with program %s (%s %s %s))\n",
	     PSviewer, PSviewer, PSviewer_opt, outname) ;
      printf("     after viewing you can also choose to print,\n") ;
      printf("   P to print logo (%s %s).)\n", PSprint, outname) ;

      fgets(ans, 2, stdin) ;

      switch (toupper(ans[0]))
	 {
         case 'V' :
            sprintf(line, "%s %s %s", PSviewer, PSviewer_opt, outname) ;
            system(line) ;
            break ;
         case 'P' :
            sprintf(line, "%s %s", PSprint, outname) ;
            system(line) ;
            printf("\nFile %s sent to printer.\n", outname) ;
            break ;
	 }
      }

}
