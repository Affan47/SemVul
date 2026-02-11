asp_send(int s, int len, char* msg, struct sockaddr* to){
  int out_stat, err, err_size = sizeof(int);

  if((out_stat = sendto(s, msg, len, 0, to, sizeof(struct sockaddr))) == -1){

#ifndef ENABLE_DEBUG
    if(errno != ECONNREFUSED) asp_perror("sendto");
#endif
  }

#ifndef ENABLE_DEBUG
if(verbose == 1) fprintf(stderr, "sent %s to: %s\n", msg, \
			 inet_ntoa(((struct sockaddr_in *)to)->sin_addr));
#endif

#ifdef ENABLE_DEBUG
    fprintf(stderr, "%s %d: sendto: %s out_stat: %d errno: %d\n", \
	    __FILE__, __LINE__, \
	    inet_ntoa(((struct sockaddr_in *)to)->sin_addr), out_stat, errno);
  if(errno != 0) fprintf(stderr, "%s\n", strerror(errno));
#endif


  if((out_stat = getsockopt(s, SOL_SOCKET, SO_ERROR, &err, &err_size)) == -1){
#ifndef ENABLE_DEBUG
    asp_perror("getsockopt");
#endif
  }

#ifdef ENABLE_DEBUG
  fprintf(stderr, "%s %d: getsockopt out_stat: %d err: %d errno: %d\n", \
	  __FILE__, __LINE__, out_stat, err, errno);
  if(errno != 0) fprintf(stderr, "%s\n", strerror(errno));
#endif

  if(err != 0) return 1;
  else return 0;
}
