_dxf_ExPathStringLen( ModPath *path )
{
  int32 i;
  int      len = 0;

  for ( i = path->num_comp-1; i >= 0; i-- )
    len += 1  +
           strlen( *FETCH_LIST( *mod_name_str_table, path->modules[i] ) ) +
           1  +
           _dxf_GetInstanceNumStringLen( path->instances[i] ) +
           1 ;

  return len;
}
