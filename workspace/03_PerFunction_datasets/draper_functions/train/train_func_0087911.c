write_aclip(char *src, size_t srclen)
{
	Lock_Display();
	XChangeProperty(SDL_Display, DefaultRootWindow(SDL_Display), XA_CUT_BUFFER0, XA_STRING, 8, PropModeReplace, (const unsigned char *)src, srclen);
	if (XGetSelectionOwner(SDL_Display, XA_PRIMARY) != SDL_Window)
		XSetSelectionOwner(SDL_Display, XA_PRIMARY, SDL_Window, CurrentTime);
	Unlock_Display();
}
