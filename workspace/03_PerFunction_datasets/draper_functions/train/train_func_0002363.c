hb_ot_layout_table_find_script (hb_face_t    *face,
				hb_tag_t      table_tag,
				hb_tag_t      script_tag,
				unsigned int *script_index)
{
  ASSERT_STATIC (OT::Index::NOT_FOUND_INDEX == HB_OT_LAYOUT_NO_SCRIPT_INDEX);
  const OT::GSUBGPOS &g = get_gsubgpos_table (face, table_tag);

  if (g.find_script_index (script_tag, script_index))
    return true;


  if (g.find_script_index (HB_OT_TAG_DEFAULT_SCRIPT, script_index))
    return false;


  if (g.find_script_index (HB_OT_TAG_DEFAULT_LANGUAGE, script_index))
    return false;


  if (g.find_script_index (HB_OT_TAG_LATIN_SCRIPT, script_index))
    return false;

  if (script_index) *script_index = HB_OT_LAYOUT_NO_SCRIPT_INDEX;
  return false;
}
