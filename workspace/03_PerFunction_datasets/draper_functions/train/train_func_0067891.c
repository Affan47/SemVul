SDL_INPUT_Restart(void)
{
	lastkey = SDLK_UNKNOWN;
	key_pressed = key_control = lastuni = 0;
	if(grab_mouse) SDL_WM_GrabInput(SDL_GRAB_ON);
}
