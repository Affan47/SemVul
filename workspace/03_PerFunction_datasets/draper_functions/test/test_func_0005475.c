setTitle( const QString &title )
{


    if( m_title.isEmpty() )
        m_directory.addPath( Amarok::vfatPath( title ) );
    m_title = title;
}
