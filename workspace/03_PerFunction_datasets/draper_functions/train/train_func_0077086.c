atom_moov_add_blob_tag (AtomMOOV * moov, guint8 * data, guint size)
{
  AtomData *data_atom;
  GstBuffer *buf;
  guint len;
  guint32 fourcc;

  if (size < 8)
    return;


  len = GST_READ_UINT32_BE (data);
  fourcc = GST_READ_UINT32_LE (data + 4);
  if (len > size)
    return;

  buf = _gst_buffer_new_wrapped (data + 8, len - 8, NULL);
  data_atom = atom_data_new_from_gst_buffer (fourcc, buf);
  gst_buffer_unref (buf);

  atom_moov_append_tag (moov,
      build_atom_info_wrapper ((Atom *) data_atom, atom_data_copy_data,
          atom_data_free));
}
