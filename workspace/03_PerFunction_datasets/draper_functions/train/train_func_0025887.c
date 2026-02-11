build_pasp_extension (AtomTRAK * trak, gint par_width, gint par_height)
{
  AtomData *atom_data;
  GstBuffer *buf;
  guint8 *data;

  buf = gst_buffer_new_and_alloc (8);
  data = GST_BUFFER_DATA (buf);


  GST_WRITE_UINT32_BE (data, par_width);
  GST_WRITE_UINT32_BE (data + 4, par_height);

  atom_data = atom_data_new_from_gst_buffer (FOURCC_pasp, buf);
  gst_buffer_unref (buf);

  return build_atom_info_wrapper ((Atom *) atom_data, atom_data_copy_data,
      atom_data_free);
}
