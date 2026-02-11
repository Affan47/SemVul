populateScrobbling()
{
    LastFmUserSettings& user = The::settings().currentUser();

    ui_scrobbling.scrobblePointSlider->setValue( user.scrobblePoint() );
    ui_scrobbling.scrobblePointLabel->setText( QString::number( user.scrobblePoint() ) );
    ui_scrobbling.launchWithMediaPlayerCheck->setChecked( The::settings().launchWithMediaPlayer() );
#ifndef LINUX
    ui_scrobbling.fingerprintCheckBox->setChecked( user.fingerprintingEnabled() );
#endif
    ui_scrobbling.dirTree->setExclusions( user.excludedDirs() );
}
