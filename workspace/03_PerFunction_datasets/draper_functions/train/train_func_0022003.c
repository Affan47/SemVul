Hsendto(	int fd , const void *msg , int msglen , unsigned int flags , const struct sockaddr *addr , int addrlen 	) {
 int r, e;
	Tmust("sendto","flags",flags==0);
 Qsendto(	fd , msg , msglen , addr , addrlen 	);
 r= sendto(	fd , msg , msglen , flags , addr , addrlen 	);
 e= errno;
 vb.used= 0;
 Tvba("sendto=");
  if (r==-1) { Tvberrno(e); goto x_error; }
  Tvbf("%d",r);
 x_error:
 R_recordtime();
 R_vb();
 errno= e;
 return r;
}
