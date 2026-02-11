getargs(argc,argv,inpfname,outfname,fam_name, lisname)
int    argc;
char   *argv[];
char   inpfname[], outfname[], fam_name[], lisname[];
{
   int i1 ;
   int fnames=0 ;
   char *chr_ptr ;

   inpfname[0] = outfname[0] = fam_name[0] = lisname[0] = '\0';

   for(i1=1; i1<argc; i1++)
      {
      if (argv[i1][0] != '-')
	 {
         if (fnames == 0)
	    {
            strcpy(inpfname,argv[i1]) ;
            fnames++ ;
	    }
         else if (fnames == 1)
	    {
            strcpy(outfname,argv[i1]) ;
            fnames++ ;
	    }
         else
            fprintf(stderr,
            "Warning unrecognized parameter - \"%s\".\n",
            argv[i1]);
	 }
      else
	 {
         switch (toupper(argv[i1][1]))
	    {
            case 'F' :
               chr_ptr = argv[i1] + 2 ;
               strcpy(fam_name,chr_ptr) ;
               break ;
            case 'L' :
               chr_ptr = argv[i1] + 2 ;
               strcpy(lisname,chr_ptr) ;
               break ;
	    case '\0' :
               fnames++ ;
               break ;
	    default :
               fprintf(stderr,
               "Warning unrecognized parameter - \"%s\".\n",
               argv[i1]);
	    }
         }
      }

      return ;
}
