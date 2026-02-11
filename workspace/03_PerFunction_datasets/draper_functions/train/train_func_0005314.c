switch_read(access,ptlun,buffer1,nwant,nrec,readopt,ngot,mod)
int  	access	;
int 	*ptlun  	;
char 	*buffer1;
int	*nwant	;
int 	*nrec	;
int	readopt	;
int	*ngot	;
int 	mod	;

{
	int status;
        if (readopt == FFREAD_C)        {
			if (mod == LLTM)
                                log(LOG_DEBUG, "rxyread(%d) SPECIAL\n",*ptlun);
			else {
				TRACE(2, "rfio", "rfio_xyread(%d) SPECIAL",*ptlun);
			}

#if defined(sun) || defined(sgi) || defined(hpux) || defined(_AIX) || ( defined(__osf__) && defined(__alpha) ) || defined(linux) || defined(_WIN32) || defined(__Lynx__) || defined( __APPLE__)
                                (void) uf_cread(ptlun, buffer1, nrec, nwant, ngot, &status);
#else
                                (void) frdc_(ptlun, buffer1, nwant, ngot, &status);
#endif

        }
        else    {
                switch (access) {
                        case FFFACC_S:
				if (mod == LLTM)
                                	log(LOG_DEBUG, "rxyread(%d) SEQUENTIAL\n",*ptlun);
				else
					TRACE(2, "rfio", "rfio_xyread(%d) SEQUENTIAL",*ptlun);
#if defined(sun) || defined(sgi) || defined(hpux) || defined(_AIX) || ( defined(__osf__) && defined(__alpha) ) || defined(linux) || defined(_WIN32) || defined(__Lynx__) || defined( __APPLE__)
                                status=usf_read(ptlun, buffer1, nwant);
#else
                                (void) frd_us_(ptlun, buffer1, nwant, &status);
#endif

                                *ngot = *nwant;
                                break;
                        case FFFACC_D:
				if (mod == LLTM)
                                	log(LOG_DEBUG, "rxyread(%d) DIRECT\n",*ptlun);
				else
					TRACE(2, "rfio", "rfio_xyread(%d) DIRECT",*ptlun);
#if defined(sun) || defined(sgi) || defined(hpux) || defined(_AIX) || ( defined(__osf__) && defined(__alpha) ) || defined(linux) || defined(_WIN32) || defined(__Lynx__) || defined( __APPLE__)
                                status =udf_read(ptlun, buffer1, nrec, nwant);
#else
                                (void) frd_ud_(ptlun, buffer1, nrec, nwant, &status);
#endif

                                *ngot = *nwant;
                                break;
                        default:
				if (mod == LLTM)
                                	log(LOG_ERR, "rxyread(%d) invalid access type: %d\n",*ptlun, access);
				else
					 TRACE(2, "rfio", "rfio_xyread(%d) invalid access type: %d",*ptlun, access);
                                *ngot = 0;
                                status = SEBADFOPT;
                }
	}
	return (status);

}
