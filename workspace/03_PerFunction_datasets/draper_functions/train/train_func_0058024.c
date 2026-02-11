_isBlacklistedFile ( dmtcp::string& path )
{
  if ((dmtcp::Util::strStartsWith(path, "/dev/") &&
       !dmtcp::Util::strStartsWith(path, "/dev/shm/")) ||
      dmtcp::Util::strStartsWith(path, "/proc/") ||
      dmtcp::Util::strStartsWith(path, dmtcp::UniquePid::getTmpDir().c_str())) {
    return true;
  }
  return false;
}
