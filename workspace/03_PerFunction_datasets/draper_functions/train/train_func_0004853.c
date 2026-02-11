NewGameSlot()
{
    if (mGameState == STATE_RUNNING && mCurRow != NULL)
    {
        int r = QMessageBox::warning( this,
                                      tr("New Game"),
                                      tr("Do you want to give in\nand start a new Game?"),
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes)
        {
            mGameInput = NULL;
            NewGame();
        }
    }
    else
    {
        mGameInput = NULL;
        NewGame();
    }
}
