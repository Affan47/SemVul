getTmpDir()
{
  dmtcp::string device = jalib::Filesystem::ResolveSymlink ( "/proc/self/fd/"
                           + jalib::XToString ( PROTECTED_TMPDIR_FD ) );
  if ( device.empty() ) {
    JWARNING ( false ) .Text ("Unable to determine DMTCP_TMPDIR, retrying.");
    setTmpDir(getenv(ENV_VAR_TMPDIR));
    device = jalib::Filesystem::ResolveSymlink ( "/proc/self/fd/"
               + jalib::XToString ( PROTECTED_TMPDIR_FD ) );
    JASSERT ( !device.empty() )
      .Text ( "Still unable to determine DMTCP_TMPDIR" );
  }
  return device;
}
