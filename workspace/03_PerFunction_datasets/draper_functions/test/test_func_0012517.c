get_llc_name (name_add_t *nt)
{


  if (nt->link_type == DLT_FDDI || nt->link_type == DLT_IEEE802)
    nt->offset += 8;
  else if (nt->link_type == DLT_EN10MB)
    nt->offset += 3;
  else
    return FALSE;
  return TRUE;
}
