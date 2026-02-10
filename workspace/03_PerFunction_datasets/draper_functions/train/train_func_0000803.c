setAutoSaveSettings( const KConfigGroup & group,
                                       bool saveWindowSize )
{
    K_D(KMainWindow);
    d->autoSaveSettings = true;
    d->autoSaveGroup = group;
    d->autoSaveWindowSize = saveWindowSize;

    if (!saveWindowSize && d->sizeTimer) {
        d->sizeTimer->stop();
    }


    applyMainWindowSettings(d->autoSaveGroup);
}
