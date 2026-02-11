ast_speech_destroy(struct ast_speech *speech)
{
	int res = 0;


	speech->engine->destroy(speech);


	ast_mutex_destroy(&speech->lock);


	if (speech->results)
		ast_speech_results_free(speech->results);


	if (speech->processing_sound)
		ast_free(speech->processing_sound);


	ast_free(speech);

	return res;
}
