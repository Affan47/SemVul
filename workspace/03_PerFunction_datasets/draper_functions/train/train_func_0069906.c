drawBoard(bool showTiles)
{
    if (gamePaused) {
        showTiles = false;
    }

    if (showTiles) {
        populateSpriteMap();
        drawTileNumber();
    } else {

        while (!items()->isEmpty()) {
            delete items()->first();
        }


        spriteMap.clear();


        QPalette palette;
        palette.setBrush(backgroundRole(), theBackground.getBackground());
        setPalette(palette);
        setAutoFillBackground(true);
    }
}
