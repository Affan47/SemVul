saveGame()
{
	if (loadedGame.isNull())
	{
		saveGameAs();
		return;
	}

	KConfig config(loadedGame);
	KConfigGroup configGroup(config.group("0 Saved Game"));

	configGroup.writeEntry("Competition", competition);
	configGroup.writeEntry("Course", filename);

	game->saveScores(&config);

	configGroup.sync();
}
