slotUnsetKGame()
{
 if (d->mGame) {
	disconnect(d->mGame, 0, this, 0);
 }
 d->mGame = 0;
 clearPages();
}
