Hconnect(	int fd , const struct sockaddr *addr , int addrlen 	) {
 int r, e;
 Qconnect(	fd , addr , addrlen 	);
 r= connect(	fd , addr , addrlen 	);
 e= errno;
 vb.used= 0;
 Tvba("connect=");
  if (r) { Tvberrno(e); goto x_error; }
  Tvba("OK");
 x_error:
 R_recordtime();
 R_vb();
 errno= e;
 return r;
}
