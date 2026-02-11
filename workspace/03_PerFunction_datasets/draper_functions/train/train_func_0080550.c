on_buttonStore_clicked()
{
    if ( QMessageBox::warning( this, tr( "Warning" ), tr( "Are you sure you want to store current color settings\nas the default settings?" ),
        QMessageBox::Ok | QMessageBox::Cancel ) == QMessageBox::Ok ) {
        m_model->saveDefaultColorSettings();
        updateButtons();
    }
}
