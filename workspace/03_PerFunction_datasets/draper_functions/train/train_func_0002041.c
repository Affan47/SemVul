NeedCacheCompatibility(int major, int minor)
{


  if(this->CacheMajorVersion == 0)
    {
    return false;
    }


  unsigned int actual_compat =
    CMake_VERSION_ENCODE(this->CacheMajorVersion, this->CacheMinorVersion, 0);
  return (actual_compat &&
          actual_compat <= CMake_VERSION_ENCODE(major, minor, 0));
}
