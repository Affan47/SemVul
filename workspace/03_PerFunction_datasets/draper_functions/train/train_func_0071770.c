set_seeds( FourByteLong seed[2], char seedIsSet[2], const int outlev, FILE *logFile ) {
	    time_t time_seed;
	 if ( (!seedIsSet[0]) && (sizeof seed[0])!=4)
	   pr(logFile, "Sizeof FourByteLong = %d, not 4.\n",
	   (int) (sizeof seed[0]));
	 if( ! seedIsSet[0] ) seed[0] = (FourByteLong) processid();
	 if( ! seedIsSet[1] ) seed[1] = (FourByteLong) time( &time_seed );
	 seedIsSet[0]  = seedIsSet[1] = 'D';
         setall(seed[0], seed[1]);
         if(outlev>=LOGMIN) pr(logFile,
	  "Random number generator was seeded with values " FBL_FMT ", " FBL_FMT ".\n",
	  seed[0], seed[1]);
	 }
