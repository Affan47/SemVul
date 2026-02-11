get_uri(fsp_link *link, fs_rid rid)
{
  if (cache[rid & CACHE_MASK].rid == rid) {
    return (xmlChar *) cache[rid & CACHE_MASK].lex;
  }

  fs_rid_vector onerid = { .length = 1, .size = 1, .data = &rid };
  fs_resource resource;
  fsp_resolve(link, FS_RID_SEGMENT(rid, segments), &onerid, &resource);

  return (xmlChar *) resource.lex;
}
