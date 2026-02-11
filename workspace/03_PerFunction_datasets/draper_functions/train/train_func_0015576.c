updateTimeout()
{

	savePosition();
	gSettings->sync();

	buildCatalog();

	int time = gSettings->value("GenOps/updatetimer", 10).toInt();
	updateTimer->stop();
	if (time != 0)
		updateTimer->start(time * 60000);
}
