rcs_find_version(metadata_t *metadata, int vid, int svid)
{
  version_t *version;

  version = metadata->md_versions;


  if (vid == LATEST)
    {


      if (metadata->md_deleted && !rcs_ignore_deleted)
	return NULL;


      if (metadata->md_dfl_vid == LATEST)
	return version;
      else
	{
	  vid = metadata->md_dfl_vid;
	  svid = metadata->md_dfl_svid;
	}
    }
  while (version && (version->v_vid > (unsigned)vid))
    version = version->v_next;

  if (!version || (version->v_vid != (unsigned)vid))
    {


      if (metadata->md_dfl_vid != LATEST)
	return metadata->md_versions;


      return NULL;
    }


  if (svid == LATEST)
    return version;
  while (version && (version->v_vid == (unsigned)vid) &&
	 (version->v_svid > (unsigned)svid))
    version = version->v_next;

  if (!version || (version->v_vid != (unsigned)vid) ||
      (version->v_svid != (unsigned)svid))
    {


      if (metadata->md_dfl_vid != LATEST)
	return metadata->md_versions;


      return NULL;
    }

  return version;
}
