atoms_recov_write_headers (FILE * f, AtomFTYP * ftyp, GstBuffer * prefix,
    AtomMOOV * moov, guint32 timescale, guint32 traks_number)
{
  if (!atoms_recov_write_version (f)) {
    return FALSE;
  }

  if (!atoms_recov_write_ftyp_info (f, ftyp, prefix)) {
    return FALSE;
  }

  if (!atoms_recov_write_moov_info (f, moov)) {
    return FALSE;
  }

  if (!atoms_recov_write_moov_timescale (f, timescale)) {
    return FALSE;
  }

  if (!atoms_recov_write_traks_number (f, traks_number)) {
    return FALSE;
  }

  return TRUE;
}
