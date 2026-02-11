main() {
  int n=-1;
  mh.msg_name=&sa4;
  mh.msg_namelen=sizeof(sa4);
  mh.msg_iov=&iv;
  mh.msg_iovlen=1;
  iv.iov_base=buf;
  iv.iov_len=PKGSIZE;
  mh.msg_control=abuf;
  mh.msg_controllen=sizeof(abuf);

  if (gethostname(myhostname,64)==-1) {
    perror("gethostname");
    return 1;
  }
  namelen=strlen(myhostname);

  init_sockets(&s6,&s4,5353,"\xff\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xfb","\xe0\x00\x00\xfb");
  init_sockets(&ls6,&ls4,5355,"\xff\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x03","\xe0\x00\x00\xfc");

  pfd[0].events=pfd[1].events=pfd[2].events=pfd[3].events=POLLIN;
  if (s6!=-1) pfd[++n].fd=s6;
  if (s4!=-1) pfd[++n].fd=s4;
  if (ls6!=-1) pfd[++n].fd=ls6;
  if (ls4!=-1) pfd[++n].fd=ls4;
  if (!++n)
    return 2;
  for (;;) {
    int i;
    switch (poll(pfd,n,5*1000)) {
    case -1:
      if (errno==EINTR) continue;
      perror("poll");
      return 1;
    case 0:
      continue;
    }
    for (i=0; i<n; ++i)
      if (pfd[i].revents & POLLIN) {
	if (pfd[i].fd==s6 || pfd[i].fd==ls6)
	  recv6(pfd[i].fd);
	else
	  recv4(pfd[i].fd);
      }
  }
  return 0;
}
