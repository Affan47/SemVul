setTmpDir(const char* envVarTmpDir) {
  dmtcp::string tmpDir;

  char hostname[256];
  memset(hostname, 0, sizeof(hostname));

  JASSERT ( gethostname(hostname, sizeof(hostname)) == 0 ||
	    errno == ENAMETOOLONG ).Text ( "gethostname() failed" );

  dmtcp::ostringstream o;

  char *userName = const_cast<char *>("");
  if ( getpwuid ( getuid() ) != NULL ) {
    userName = getpwuid ( getuid() ) -> pw_name;
  } else if ( getenv("USER") != NULL ) {
    userName = getenv("USER");
  }

  if (envVarTmpDir) {
    o << envVarTmpDir;
  } else if (getenv("TMPDIR")) {
    o << getenv("TMPDIR") << "/dmtcp-" << userName << "@" << hostname;
  } else {
    o << "/tmp/dmtcp-" << userName << "@" << hostname;
  }

  JASSERT(mkdir(o.str().c_str(), S_IRWXU) == 0 || errno == EEXIST)
    (JASSERT_ERRNO) (o.str())
    .Text("Error creating tmp directory");

  JASSERT(0 == access(o.str().c_str(), X_OK|W_OK)) (o.str())
    .Text("ERROR: Missing execute- or write-access to tmp dir");

  int tmpFd = open ( o.str().c_str(), O_RDONLY  );
  JASSERT(tmpFd != -1);
  JASSERT(dup2(tmpFd, PROTECTED_TMPDIR_FD)==PROTECTED_TMPDIR_FD);
  close ( tmpFd );
}
