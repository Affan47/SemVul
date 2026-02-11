addLabelPressed()
{
    QString label = ui->kComboBox_label->currentText();

    if( !label.isEmpty() )
    {
        m_labelModel->addLabel( label );
        ui->kComboBox_label->setCurrentIndex( -1 );
        ui->kComboBox_label->completionObject()->insertItems( QStringList( label ) );

        if ( !ui->kComboBox_label->contains( label ) )
            ui->kComboBox_label->addItem( label );

        checkChanged();
    }
}
