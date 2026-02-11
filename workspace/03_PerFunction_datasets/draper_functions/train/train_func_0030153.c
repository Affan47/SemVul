m_emit_info_init (pIIR_FileType ft, string &str, RegionStack &rstack, bool static_info, int l)
{
  str += ".set(" + get_type_info_obj(ft->type_mark, rstack, false) + ")";

  return get_static_level(ft, rstack);
}
