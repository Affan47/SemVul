setIcon( const KIcon &icon )
{
    d->item.setIcon(icon);

    if ( s_useIcons || text().isEmpty() )
        QPushButton::setIcon( icon );
    else
        QPushButton::setIcon( QIcon() );
}
