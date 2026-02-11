get_attr(fsp_link *link, fs_rid rid)
{
  fs_rid_vector onerid = { .length = 1, .size = 1, .data = &rid };
  fs_resource resource;
  if (fsp_resolve(link, FS_RID_SEGMENT(rid, segments), &onerid, &resource)) {
    return "#error attr#";
  }

  return (char *) resource.lex;
}
