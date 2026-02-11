intro()
{
	char buf[100];

	sprintf(buf,"%s", strwide(PACKAGE));
	if (typewriter(buf, -1, -1) == 0)
		return;

	sprintf(buf,"%s  %s", strwide("version"), strwide(VERSION));
	if (typewriter(buf, -1, sl_screen_height/2+1) == 0)
		return;

	usleep(200*1000);
	clear = 1;
}
