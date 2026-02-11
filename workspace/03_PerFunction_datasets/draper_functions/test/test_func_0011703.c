ast_tone_zone_sound_destructor(void *obj)
{
	struct ast_tone_zone_sound *ts = obj;


	if (ts->name) {
		ast_free((char *) ts->name);
		ts->name = NULL;
	}

	if (ts->data) {
		ast_free((char *) ts->data);
		ts->data = NULL;
	}
}
