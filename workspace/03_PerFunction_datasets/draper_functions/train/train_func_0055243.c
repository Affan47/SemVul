SaveScreen(bool save)
{
    if (saved != save) {
	saved = save;
	vInfo.screen_saver(save);
    }
    saverCount = 0;
}
