saveOK ()
{
    bool result = true;

    if ((shouldSave) || (levelData.layout != savedLevelData.layout)) {

        switch (KGrMessage::warning (view, i18n ("Editor"),
                    i18n ("You have not saved your work. Do "
                    "you want to save it now?"),
                    i18n ("&Save"), i18n ("&Do Not Save"),
                    i18n ("&Go on editing")))
        {
        case 0:
            result = saveLevelFile();
            break;
        case 1:
            shouldSave = false;
            break;
        case 2:
            result = false;
            break;
        }
    }

    return (result);
}
