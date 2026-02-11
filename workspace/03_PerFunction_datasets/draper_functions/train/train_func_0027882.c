Hsocket(	int domain , int type , int protocol 	) {
 int r, e;
	Tmust("socket","domain",domain==AF_INET);
  Tmust("socket","type",type==SOCK_STREAM || type==SOCK_DGRAM);
 Qsocket(	 type 	);
 r= socket(	domain , type , protocol 	);
 e= errno;
 vb.used= 0;
 Tvba("socket=");
  if (r==-1) { Tvberrno(e); goto x_error; }
  Tvbf("%d",r);
 x_error:
 R_recordtime();
 R_vb();
 errno= e;
 return r;
}
