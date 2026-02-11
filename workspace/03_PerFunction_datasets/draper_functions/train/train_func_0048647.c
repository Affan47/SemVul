atom_tag_new (guint32 fourcc, guint32 flags_as_uint)
{
  AtomTag *tag = g_new0 (AtomTag, 1);

  tag->header.type = fourcc;
  atom_tag_data_init (&tag->data);
  atom_full_set_flags_as_uint (&tag->data.header, flags_as_uint);
  return tag;
}
