getFont( QFont &theFont,
                          const KFontChooser::DisplayFlags& flags,
                          QWidget *parent,
                          Qt::CheckState *sizeIsRelativeState )
{
    KFontDialog dlg( parent, flags, QStringList(), sizeIsRelativeState );
    dlg.setModal( true );
    dlg.setObjectName( "Font Selector" );
    dlg.setFont( theFont, flags & KFontChooser::FixedFontsOnly );

    int result = dlg.exec();
    if( result == Accepted )
    {
        theFont = dlg.d->chooser->font();
        if( sizeIsRelativeState )
            *sizeIsRelativeState = dlg.d->chooser->sizeIsRelative();
    }
    return result;
}
