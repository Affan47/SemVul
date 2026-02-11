setSettingsDirty(CallCompression callCompression)
{
    if (!letDirtySettings) {
        return;
    }

    settingsDirty = true;
    if (autoSaveSettings) {
        if (callCompression == CompressCalls) {
            if (!settingsTimer) {
                settingsTimer = new QTimer(q);
                settingsTimer->setInterval(500);
                settingsTimer->setSingleShot(true);
                QObject::connect(settingsTimer, SIGNAL(timeout()), q, SLOT(saveAutoSaveSettings()));
            }
            settingsTimer->start();
        } else {
            q->saveAutoSaveSettings();
        }
    }
}
