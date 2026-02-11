moveChars(u16 sx, u16 sy, u16 dx, u16 dy, u16 w, u16 h)
{
	if (manager->activeShell() != this) return true;
	return screen->move(sx, sy, dx, dy, w, h);
}
