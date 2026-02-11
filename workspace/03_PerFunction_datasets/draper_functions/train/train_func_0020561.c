html_entities_init(void)
{
	size_t i;

	html_entities_lut = htable_create(HASH_KEY_STRING, 0);
	for (i = 0; i < G_N_ELEMENTS(html_entities); i++) {
		htable_insert(html_entities_lut, html_entities[i].name,
			uint_to_pointer(html_entities[i].uc));
	}
}
