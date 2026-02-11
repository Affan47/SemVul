runNextDemoLevel()
{
    dbk << "index" << playbackIndex << "max" << playbackMax << playbackPrefix
        << "owner" << playbackOwner;
    if (playbackIndex < playbackMax) {
        playbackIndex++;
        if (playLevel (playbackOwner, playbackPrefix,
                       playbackIndex, (! NewLevel))) {
            if (levelPlayer) {
                levelPlayer->prepareToPlay();
            }
            kDebug() << "DEMO continued ..." << playbackPrefix << playbackIndex;
            return;
        }
    }
    finishDemo();
}
