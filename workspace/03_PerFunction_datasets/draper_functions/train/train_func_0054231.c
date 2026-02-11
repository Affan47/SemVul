set_volume(int str_num, int level)
{
	if (!is_available) return;


	SDL_mutexP(mutex);


	global_volume = level;


	SDL_mutexV(mutex);
}
