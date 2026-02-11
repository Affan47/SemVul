engine_close()  {

	frame_destroy_all();
	if(engine->table_alpha_is_init) eng_free_alpha_table();
	g_free(engine);

#if ENG_DEBUG
	fprintf(stdout, "Closing engine...\n");
#endif
}
