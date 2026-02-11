exit()
{
	gTrayIcon *icon;

	while((icon = get(0)))
		delete icon;
}
