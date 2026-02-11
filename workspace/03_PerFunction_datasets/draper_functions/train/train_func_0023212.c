check_mail_update(const char *s, int more)
{
	int h = 0, c = 0, new_count = 0;
	list_t l;

	if (!s || !xstrchr(s, ','))
		return -1;

	h = atoi(s);
	c = atoi(xstrchr(s, ',') + 1);

	for (l = mail_folders; l; l = l->next) {
		struct mail_folder *m = l->data;

		if (m->fhash == h)
			m->count = c;

		new_count += m->count;
	}

	if (new_count == mail_count)
		return 0;

	if (!more) {
		last_mail_count = mail_count;
		mail_count = new_count;
	}

	if (!more && mail_count && mail_count > last_mail_count) {
		if (config_check_mail & 4) {
			if (mail_count == 1)
				print("new_mail_one");
			else {
				if (mail_count >= 2 && mail_count <= 4)
					print("new_mail_two_four", itoa(mail_count));
				else
					print("new_mail_more", itoa(mail_count));
			}
		}

		if (config_beep && config_beep_mail)
			query_emit_id(NULL, UI_BEEP, NULL);

		play_sound(config_sound_mail_file);


	}

	return 0;
}
