lt_tag_get_string(lt_tag_t *tag)
{
	lt_list_t *l;

	if (tag->tag_string)
		return lt_string_value(tag->tag_string);

	if (tag->grandfathered)
		lt_tag_add_tag_string(tag, lt_grandfathered_get_tag(tag->grandfathered));
	else if (tag->language) {
		lt_tag_add_tag_string(tag, lt_lang_get_tag(tag->language));
		if (tag->extlang)
			lt_tag_add_tag_string(tag, lt_extlang_get_tag(tag->extlang));
		if (tag->script)
			lt_tag_add_tag_string(tag, lt_script_get_tag(tag->script));
		if (tag->region)
			lt_tag_add_tag_string(tag, lt_region_get_tag(tag->region));
		l = tag->variants;
		while (l != NULL) {
			lt_tag_add_tag_string(tag, lt_variant_get_tag(lt_list_value(l)));
			l = lt_list_next(l);
		}
		if (tag->extension)
			lt_tag_add_tag_string(tag, lt_extension_get_tag(tag->extension));
		if (tag->privateuse && lt_string_length(tag->privateuse) > 0)
			lt_tag_add_tag_string(tag, lt_string_value(tag->privateuse));
	} else if (tag->privateuse && lt_string_length(tag->privateuse) > 0) {
		lt_tag_add_tag_string(tag, lt_string_value(tag->privateuse));
	} else {
		return NULL;
	}

	return lt_string_value(tag->tag_string);
}
