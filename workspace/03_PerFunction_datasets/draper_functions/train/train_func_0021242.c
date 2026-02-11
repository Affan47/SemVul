editingEnded()
{
	delete editor;
	editor = 0;

	if (scoreboard)
		scoreboard->show();

	clearHoleAction->setEnabled(false);
	newHoleAction->setEnabled(false);
	setHoleOtherEnabled(true);

	if (game)
		game->setFocus();
}
