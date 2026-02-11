updateToolTip()
{
    if( m_track )
    {
        setToolTipTitle( The::engineController()->prettyNowPlaying( false ) );

        QStringList tooltip;

        QString volume;
        if ( The::engineController()->isMuted() )
        {
            volume = i18n( "Muted" );
        }
        else
        {
            volume = i18n( "%1%", The::engineController()->volume() );
        }
        tooltip << i18n( "<i>Volume: %1</i>", volume );

        Meta::StatisticsPtr statistics = m_track->statistics();
        const float score = statistics->score();
        if( score > 0.f )
        {
            tooltip << i18n( "Score: %1", QString::number( score, 'f', 2 ) );
        }

        const int rating = statistics->rating();
        if( rating > 0 )
        {
            QString stars;
            for( int i = 0; i < rating / 2; ++i )
                stars += QString( "<img src=\"%1\" height=\"%2\" width=\"%3\">" )
                        .arg( KStandardDirs::locate( "data", "amarok/images/star.png" ) )
                        .arg( QFontMetrics( QToolTip::font() ).height() )
                        .arg( QFontMetrics( QToolTip::font() ).height() );
            if( rating % 2 )
                stars += QString( "<img src=\"%1\" height=\"%2\" width=\"%3\">" )
                        .arg( KStandardDirs::locate( "data", "amarok/images/smallstar.png" ) )
                        .arg( QFontMetrics( QToolTip::font() ).height() )
                        .arg( QFontMetrics( QToolTip::font() ).height() );

            tooltip << i18n( "Rating: %1", stars );
        }

        const int count = statistics->playCount();
        if( count > 0 )
        {
            tooltip << i18n( "Play count: %1", count );
        }

        const QDateTime lastPlayed = statistics->lastPlayed();
        tooltip << i18n( "Last played: %1", Amarok::verboseTimeSince( lastPlayed ) );

        setToolTipSubTitle( tooltip.join("<br>") );
    }
    else
    {
        setToolTipTitle( KCmdLineArgs::aboutData()->programName() );
        setToolTipSubTitle( The::engineController()->prettyNowPlaying( false ) );
    }
}
