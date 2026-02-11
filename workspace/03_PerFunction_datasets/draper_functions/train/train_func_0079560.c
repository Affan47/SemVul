GetDisabledTrayIcon( MooseEnums::UserIconColour eColour )
{
    if ( !mbIconsLoaded )
        LoadIcons();

    if ( maDisabledTrayIcons[ eColour ].isNull() )
        return QPixmap( 22, 22 );
    else
        return maDisabledTrayIcons[ eColour ];
}
