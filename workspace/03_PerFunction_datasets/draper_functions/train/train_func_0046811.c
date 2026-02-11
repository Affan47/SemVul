themeDirsChanged()
    {
        if (q->existingIconThemeDirs(mThemeNames) != mThemeDirs ||
            q->mostRecentMTime(mThemeDirs) != mThemesMTime) {
            kDebug(264) << "Theme directory has been modified";
            return true;
        } else {
            return false;
        }
    }
