playLevel (const Owner fileOwner, const QString & prefix,
                         const int levelNo, const bool newLevel)
{

    if (editor) {
        emit setEditMenu (false);
        delete editor;
        editor = 0;
    }


    if (levelPlayer) {
        endLevel (NORMAL);
    }


    scene->deleteAllSprites();


    if (! initRecordingData (fileOwner, prefix, levelNo)) {
        return false;
    }

    scene->setLevel (levelNo);
    scene->fadeIn (true);
    startScore = score;


    setupLevelPlayer();

    levelName = recording->levelName;
    levelHint = recording->hint;


    emit hintAvailable (levelHint.length() > 0);


    scene->setTitle (getTitle());


    if (newLevel && (level != 0)) {
        KConfigGroup gameGroup (KGlobal::config(), "KDEGame");
        gameGroup.writeEntry ("GamePrefix", prefix);
        gameGroup.writeEntry ("Level_" + prefix, level);
        gameGroup.sync();
    }

    return true;
}
