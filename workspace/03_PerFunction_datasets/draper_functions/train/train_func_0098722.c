mxf_is_body_partition_pack (const MXFUL * ul)
{
  if (mxf_is_partition_pack (ul) && ul->u[13] == 0x03)
    return TRUE;

  return FALSE;
}
