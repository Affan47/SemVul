is_proc_ref_file_void_or_format (MOID_T * p)
{
  if (p == MODE (PROC_REF_FILE_VOID)) {
    return (A68_TRUE);
  } else if (p == MODE (FORMAT)) {
    return (A68_TRUE);
  } else {
    return (A68_FALSE);
  }
}
