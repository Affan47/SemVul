editor()
{
    if( m_localFile )
        return m_localFile->editor();
    else
        return Meta::TrackEditorPtr();
}
