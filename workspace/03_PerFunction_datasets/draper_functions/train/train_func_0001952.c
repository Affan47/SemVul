on_buttonType_clicked()
{
    FractalTypeDialog dialog( this, m_model );

    if ( dialog.exec() == QDialog::Accepted )
        m_model->setParameters( dialog.fractalType(), dialog.position() );
}
