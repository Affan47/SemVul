applyIconChanges()
{
    KIconButton *iconButton = qobject_cast<KIconButton*>(d->iconArea);
    if ( !iconButton || !d->bIconChanged )
        return;


    KUrl url = properties->kurl();
    url = KIO::NetAccess::mostLocalUrl( url, properties );
    if ( url.isLocalFile()) {
        QString path;

        if (S_ISDIR(properties->item().mode()))
        {
            path = url.toLocalFile(KUrl::AddTrailingSlash) + QString::fromLatin1(".directory");


        }
        else
            path = url.toLocalFile();


        QString str = KMimeType::findByUrl( url,
                                            properties->item().mode(),
                                            true )->iconName();

        QString sIcon;
        if ( str != iconButton->icon() )
            sIcon = iconButton->icon();


        kDebug(250) << "**" << path << "**";


        if ( !sIcon.isEmpty() || QFile::exists(path) )
        {
            KDesktopFile cfg(path);
            kDebug(250) << "sIcon = " << (sIcon);
            kDebug(250) << "str = " << (str);
            cfg.desktopGroup().writeEntry( "Icon", sIcon );
            cfg.sync();

            cfg.reparseConfiguration();
            if ( cfg.desktopGroup().readEntry("Icon") != sIcon ) {
                KMessageBox::sorry( 0, i18n("<qt>Could not save properties. You do not "
                                            "have sufficient access to write to <b>%1</b>.</qt>", path));
            }
        }
    }
}
