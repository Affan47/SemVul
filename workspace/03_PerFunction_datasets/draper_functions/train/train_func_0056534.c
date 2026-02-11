on_buttonLoad_clicked()
{
    LoadBookmarkDialog dialog( this );
    dialog.setModel( m_model );
    dialog.exec();
}
