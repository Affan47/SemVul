initRecordingData (const Owner fileOwner, const QString & prefix,
                                 const int levelNo)
{

    delete recording;
    recording = new KGrRecording;
    recording->content.fill (0, 4000);
    recording->draws.fill   (0, 400);


    const QString dir = ((fileOwner == SYSTEM) || (levelNo == 0)) ?
                        systemDataDir : userDataDir;
    if (playback) {
        kDebug() << "loadRecording" << dir << prefix << levelNo;
        if (! loadRecording (dir, prefix, levelNo)) {
            return false;
        }
    }
    else {
        KGrGameIO    io (view);
        KGrLevelData levelData;


        if (! io.readLevelData (dir, prefix, levelNo, levelData)) {
            return false;
        }

        recording->dateTime    = QDateTime::currentDateTime()
                                              .toUTC()
                                              .toString (Qt::ISODate);
        kDebug() << "Recording at" << recording->dateTime;

        KGrGameData * gameData = gameList.at (gameIndex);
        recording->owner       = gameData->owner;
        recording->rules       = gameData->rules;
        recording->prefix      = gameData->prefix;
        recording->gameName    = gameData->name;

        recording->level       = levelNo;
        recording->width       = levelData.width;
        recording->height      = levelData.height;
        recording->layout      = levelData.layout;


        recording->levelName   = (levelData.name.size() > 0) ?
                                 i18n (levelData.name.constData()) : "";
        recording->hint        = (levelData.hint.size() > 0) ?
                                 i18n (levelData.hint.constData()) : "";

        recording->lives       = lives;
        recording->score       = score;
        recording->speed       = timeScale;
        recording->controlMode = controlMode;
        recording->keyOption   = holdKeyOption;
        recording->content [0] = 0xff;
    }
    return true;
}
