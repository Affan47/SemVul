checkkey( sock, key )
int sock;
u_short  key;
{
	int rcode ;
	int magic ;
	int answer;
	char marsh_buf[64] ;
	char *ptr;
	ptr = marsh_buf ;

	marshall_LONG(ptr,RFIO2TPREAD_MAGIC);
	marshall_LONG(ptr,(LONG)key);
	marshall_LONG(ptr, 0);


        if ( netwrite_timeout(sock,marsh_buf,3*LONGSIZE,RFIO_CTRL_TIMEOUT) != (3*LONGSIZE) ) {
                log(LOG_ERR,"netwrite(): %s\n", strerror(errno)) ;
                return -1 ;
        }


	if ( (rcode= netread_timeout(sock,marsh_buf,LONGSIZE*3,RFIO_CTRL_TIMEOUT)) != (LONGSIZE*3) ) {
                log(LOG_ERR,"netread(): %s\n",strerror(errno)) ;
                (void) close(sock) ;
                return -1 ;
	}
	ptr = marsh_buf ;
	if ( rcode == 0 ) {
                log(LOG_ERR,"connection closed by remote end\n") ;
                (void) close(sock) ;
                return -1 ;
        }
	unmarshall_LONG(ptr,magic);
	if ( magic != RFIO2TPREAD_MAGIC ) {
		log(LOG_ERR,"Magic inconsistency. \n");
		return -1 ;
	}
	unmarshall_LONG(ptr,answer);
	if ( answer==OK ) {
		log(LOG_DEBUG,"Key is correct.\n");
		return 1 ;
	}
	else
		return 0 ;
}
