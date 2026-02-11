_dxf_ExPathToString( ModPath *path )
{
  static char str[ MAX_PATH_STR_LEN ];
  int len;

  len = _dxf_ExPathStringLen( path );

  if ( len >= sizeof(str) ) {
    _dxf_ExDie ("_dxf_ExPathToString:  Path is too long");
    return NULL;
  }

  _dxf_ExPathToStringBuf( path, str );
  return str;
}
