ambigousTrack( Meta::TrackList tracks, QString oldUrl )
{
    Q_UNUSED( tracks );

    QString text;

    text = i18nc( "Track has been matched ambigously, format: Url",
                  "Multiple ambiguous matches found for <b><font color='red'>%1</font></b>, has been discarded.", oldUrl );
    m_results->appendHtml( text );
}
