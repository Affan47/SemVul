sdl_ButtonBankNew(sdl_ButtonBank *bank)
{
	int i = 0;
	sdl_Button *new_button;

	while (bank->used[i] && (i < MAX_BUTTONS)) i++;

	if (i == MAX_BUTTONS)
	{

		return (-1);
	}


	new_button = &bank->buttons[i];


	bank->used[i] = TRUE;


	WIPE(new_button, sdl_Button);


	new_button->owner = bank;


	new_button->unsel_colour = SDL_MapRGB(bank->window->surface->format, 160, 160, 60);
	new_button->sel_colour = SDL_MapRGB(bank->window->surface->format, 210, 210, 110);
	new_button->cap_colour = SDL_MapRGB(bank->window->surface->format, 0, 0, 0);


	return (i);
}
