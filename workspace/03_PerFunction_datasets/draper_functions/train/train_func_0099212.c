closeEvent(QCloseEvent *e)
{
    if (testSave()) {
        theBoard.clearBoardLayout();
        clean = true;
        numTiles = 0;
        statusChanged();
        update();


        Prefs::setEditorGeometry(geometry());
        Prefs::self()->writeConfig();

        e->accept();
    } else {
        e->ignore();
    }
}
