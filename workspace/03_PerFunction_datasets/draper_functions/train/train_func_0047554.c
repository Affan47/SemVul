shouldRestart( bool forceAsking, bool showNumMatches ) const
{


    if ( !forceAsking && (d->options & KFind::FromCursor) == 0 )
    {
        displayFinalDialog();
        return false;
    }
    QString message;
    if ( showNumMatches )
    {
        if ( numMatches() )
            message = i18np( "1 match found.", "%1 matches found.", numMatches() );
        else
            message = i18n("No matches found for '<b>%1</b>'.", Qt::escape(d->pattern));
    }
    else
    {
        if ( d->options & KFind::FindBackwards )
            message = i18n( "Beginning of document reached." );
        else
            message = i18n( "End of document reached." );
    }

    message += "<br><br>";

    message +=
        ( d->options & KFind::FindBackwards ) ?
        i18n("Continue from the end?")
        : i18n("Continue from the beginning?");

    int ret = KMessageBox::questionYesNo( dialogsParent(), "<qt>"+message+"</qt>",
                                          QString(), KStandardGuiItem::cont(), KStandardGuiItem::stop() );
    bool yes = ( ret == KMessageBox::Yes );
    if ( yes )
        const_cast<KFind*>(this)->d->options &= ~KFind::FromCursor;
    return yes;
}
