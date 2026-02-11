close_audio(void)
{
	size_t i;
	int j;


	for (i = 0; i < MSG_MAX; i++)
	{
  		sample_list *smp = &samples[i];


		for (j = 0; j < smp->num; j++)
		{
			Mix_FreeChunk(smp->wavs[j]);
			string_free(smp->paths[j]);
		}
	}


	Mix_CloseAudio();


	SDL_Quit();
}
