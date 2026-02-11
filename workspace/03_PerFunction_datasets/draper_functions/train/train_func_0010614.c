_lt_tag_subtract(lt_tag_t       *tag,
		 const lt_tag_t *rtag)
{
	if (rtag->language) {
		lt_tag_free_language(tag);
	}
	if (rtag->extlang) {
		lt_tag_free_extlang(tag);
	}
	if (rtag->script) {
		lt_tag_free_script(tag);
	}
	if (rtag->region) {
		lt_tag_free_region(tag);
	}
	if (rtag->variants) {
		lt_tag_free_variants(tag);
	}
	if (rtag->extension) {

		lt_tag_free_extension(tag);
	}
	if (rtag->privateuse) {
		if (tag->privateuse)
			lt_string_clear(tag->privateuse);
	}
}
