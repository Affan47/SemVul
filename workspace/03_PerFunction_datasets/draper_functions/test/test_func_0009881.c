addSetsockopt ( int level, int option, const char* value, int len )
{
  _sockOptions[level][option] = jalib::JBuffer ( value, len );
}
