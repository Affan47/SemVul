hb_face_get_table (hb_face_t *face,
		   hb_tag_t   tag)
{
  if (HB_UNLIKELY (!face || !face->get_table))
    return hb_blob_create_empty ();

  return face->get_table (tag, face->user_data);
}
