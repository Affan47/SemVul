single_init(void)
{
	struct db_salt *salt;

	log_event("Proceeding with \"single crack\" mode");

	progress = 0;

	length = single_db->format->params.plaintext_length;
	key_count = single_db->format->params.min_keys_per_crypt;
	if (key_count < SINGLE_HASH_MIN)
		key_count = SINGLE_HASH_MIN;


	if (key_count > 0x8000)
		key_count = 0x8000;
	while (key_count > 0xffff / length + 1)
		key_count >>= 1;

	if (rpp_init(rule_ctx, SUBSECTION_SINGLE)) {
		log_event("! No \"single crack\" mode rules found");
		if (john_main_process)
			fprintf(stderr,
			    "No \"single crack\" mode rules found in %s\n",
			    cfg_name);
		error();
	}

	rules_init(length);
	rec_rule = rule_number = 0;
	rule_count = rules_count(rule_ctx, 0);

	log_event("- %d preprocessed word mangling rules", rule_count);

	status_init(get_progress, 0);

	rec_restore_mode(restore_state);
	rec_init(single_db, save_state);

	salt = single_db->salts;
	do {
		single_alloc_keys(&salt->keys);
	} while ((salt = salt->next));

	if (key_count > 1)
	log_event("- Allocated %d buffer%s of %d candidate passwords%s",
		single_db->salt_count,
		single_db->salt_count != 1 ? "s" : "",
		key_count,
		single_db->salt_count != 1 ? " each" : "");

	guessed_keys = NULL;
	single_alloc_keys(&guessed_keys);

	crk_init(single_db, NULL, guessed_keys);
}
