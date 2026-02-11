main(int argc, char **argv){
  ssh_session session;
	if(opts(argc,argv)<0)
    return EXIT_FAILURE;
  session=connect_ssh(destination,NULL,verbosity);
  if(session == NULL)
  	return EXIT_FAILURE;
  do_sftp(session);
  ssh_disconnect(session);
  ssh_free(session);
  return 0;
}
