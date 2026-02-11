slPaintLevel()
{

    if (slGameIndex < 0) {
        return;
    }

    QString dir = (myGameList.at (slGameIndex)->owner == USER) ?
                                  userDir : systemDir;
    thumbNail->setLevelData (dir, myGameList.at (slGameIndex)->prefix,
                                  number->value(), slName);
    thumbNail->repaint();
}
