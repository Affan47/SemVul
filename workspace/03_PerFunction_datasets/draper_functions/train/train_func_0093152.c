showLaunchy(bool noFade)
{
	shouldDonate();
	showAlternatives(false);

#ifdef Q_WS_WIN


#endif
	loadPosition(pos());

	fader->fadeIn(noFade || alwaysShowLaunchy);


#ifdef Q_WS_WIN


	SetForegroundWindowEx(winId());
#endif
	input->raise();
	input->activateWindow();
	input->selectAll();
	input->setFocus();
	qApp->syncX();

	plugins.showLaunchy();
}
