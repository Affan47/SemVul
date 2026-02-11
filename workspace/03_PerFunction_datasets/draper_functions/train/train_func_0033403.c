lt_tag_add_tag_string(lt_tag_t   *tag,
		      const char *s)
{
	if (!tag->tag_string) {
		tag->tag_string = lt_string_new(NULL);
		lt_mem_add_ref(&tag->parent, tag->tag_string,
			       (lt_destroy_func_t)lt_string_unref);
	}
	if (s) {
		if (lt_string_length(tag->tag_string) > 0)
			lt_string_append_c(tag->tag_string, '-');
		lt_string_append(tag->tag_string, s);
	} else {
		lt_warn_if_reached();
	}
}
