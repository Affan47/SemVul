CheckOpts(int argc,char **argv)

{ extern char *optarg;
 int optindex = 0;
 int c;

umask(077);
sprintf(VPREFIX,"cfenvd");
openlog(VPREFIX,LOG_PID|LOG_NOWAIT|LOG_ODELAY,LOG_DAEMON);

strcpy(CFLOCK,"cfenvd");

SetContext("cfenvd");


IGNORELOCK = false;
OUTPUT[0] = '\0';

while ((c=getopt_long(argc,argv,"d:vhHFVT",CFDENVOPTIONS,&optindex)) != EOF)
  {
  switch ((char) c)
      {
      case 'd':

                switch ((optarg==NULL)?3:*optarg)
                   {
                   case '1': D1 = true;
                             break;
                   case '2': D2 = true;
                             break;
                   default:  DEBUG = true;
                             break;
                   }

                NO_FORK = true;
                printf("cfenvd: Debug mode: running in foreground\n");
                break;

      case 'v': VERBOSE = true;
         break;

      case 'V': printf("GNU %s-%s daemon\n%s\n",PACKAGE,VERSION,COPYRIGHT);
         printf("This program is covered by the GNU General Public License and may be\n");
         printf("copied free of charge. No warrenty is implied.\n\n");
         exit(0);
         break;

      case 'F': NO_FORK = true;
         break;

      case 'H': HISTO = true;
         break;

      case 'T': TCPDUMP = true;
                break;

      default:  Syntax();
                exit(1);

      }
   }

LOGGING = true;

SetReferenceTime(false);
SetStartTime(false);
SetSignals();
signal (SIGTERM,HandleSignal);
signal (SIGHUP,HandleSignal);
signal (SIGINT,HandleSignal);
signal (SIGPIPE,HandleSignal);
signal (SIGSEGV,HandleSignal);
signal (SIGUSR1,HandleSignal);
signal (SIGUSR2,HandleSignal);
}
