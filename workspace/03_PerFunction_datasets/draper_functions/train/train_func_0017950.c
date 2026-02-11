CheckOpts(int argc,char **argv)

{ extern char *optarg;
  int optindex = 0;
  int c;


strcpy(CFWORKDIR,WORKDIR);
FLNAME[0] = '\0';
ERASE[0] = '\0';
VERBOSE = false;

if (geteuid() > 0)
   {
   char *homedir;
   if ((homedir = getenv("HOME")) != NULL)
      {
      strcpy(CFWORKDIR,homedir);
      strcat(CFWORKDIR,"/.cfagent");
      }
   }

snprintf(FILENAME,CF_BUFSIZE,"%s/state/%s",CFWORKDIR,CF_AVDB_FILE);

while ((c=getopt_long(argc,argv,"Thtf:o:rsenNEv:",GRAPHOPTIONS,&optindex)) != EOF)
  {
  switch ((char) c)
      {
      case 'E':
          strncpy(ERASE,optarg,CF_BUFSIZE-1);
          break;

      case 't':
          TITLES = true;
          break;

      case 'f':
          strcpy(FILENAME,optarg);
          break;

      case 'o': strcpy(FLNAME,optarg);
          Verbose("Setting output directory to s\n",FLNAME);
          break;

      case 'T': TIMESTAMPS = true;
          break;

      case 'v': VERBOSE = true;
         break;

      case 'r': HIRES = true;
         break;

      case 's': SEPARATE = true;
          break;

      case 'e': ERRORBARS = false;
          break;

      case 'n': NOSCALING = true;
          break;

      case 'N': NOWOPT = true;
          break;

      default:  Syntax();
                exit(1);

      }
   }
}
