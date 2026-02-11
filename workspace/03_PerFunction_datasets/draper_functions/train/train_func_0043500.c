_hb_ot_layout_collect_lookups_languages (hb_face_t      *face,
					 hb_tag_t        table_tag,
					 unsigned int    script_index,
					 const hb_tag_t *languages,
					 const hb_tag_t *features,
					 hb_set_t       *lookup_indexes )
{
  _hb_ot_layout_collect_lookups_features (face,
					  table_tag,
					  script_index,
					  HB_OT_LAYOUT_DEFAULT_LANGUAGE_INDEX,
					  features,
					  lookup_indexes);

  if (!languages)
  {

    unsigned int count = hb_ot_layout_script_get_language_tags (face,
								table_tag,
								script_index,
								0, NULL, NULL);
    for (unsigned int language_index = 0; language_index < count; language_index++)
      _hb_ot_layout_collect_lookups_features (face,
					      table_tag,
					      script_index,
					      language_index,
					      features,
					      lookup_indexes);
  }
  else
  {
    for (; *languages; languages++)
    {
      unsigned int language_index;
      if (hb_ot_layout_script_find_language (face,
					     table_tag,
					     script_index,
					     *languages,
					     &language_index))
        _hb_ot_layout_collect_lookups_features (face,
						table_tag,
						script_index,
						language_index,
						features,
						lookup_indexes);
    }
  }
}
