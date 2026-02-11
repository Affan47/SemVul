showPreview( const KUrl &url )
{
    d->controls->setEnabled(false);
    if (!d->player) {
        d->player = new MediaObject(this);
        Phonon::createPath(d->player, d->videoWidget);
        Phonon::createPath(d->player, d->audioOutput);
        connect(d->player, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
                SLOT(stateChanged(Phonon::State,Phonon::State)));
        d->videoWidget->setVisible(d->player->hasVideo());
        connect(d->player, SIGNAL(hasVideoChanged(bool)), d->videoWidget, SLOT(setVisible(bool)));
        d->controls->setMediaObject(d->player);
    }
    d->player->setCurrentSource(url);

    if( m_autoPlay->isChecked() )
        d->player->play();
}
