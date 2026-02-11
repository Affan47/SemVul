eventKeyDown(const SDL_KeyboardEvent* key) {
	SDLKey ckey = PG_LogConsole::GetConsoleKey();

	if(ckey == 0) {
		return false;
	}

	if (key->keysym.sym == ckey) {
		PG_LogConsole::Update();
		PG_LogConsole::Toggle();
		return true;
	}

	return false;
}
