onHotkey()
{
	if (menuOpen || optionsOpen)
	{
		showLaunchy(true);
		return;
	}
	if (!alwaysShowLaunchy && isVisible() && !fader->isFading() && QApplication::activeWindow() !=0)
	{
		hideLaunchy();
	}
	else
	{
		showLaunchy();
	}
}
