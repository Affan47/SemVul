selectedPlugin()
{
    QLayout* layout = ui.blankWidget->layout();

    QLayoutItem* item;
    for( int index = 0; ( item = layout->itemAt( index ) ); index++ )
    {
        QRadioButton* radioButton = static_cast<QRadioButton*>( item->widget() );
        if( radioButton->isChecked() )
        {
            if( index < static_cast<int>( mPlugins.size() ) )
                return &mPlugins[ index ];
        }
    }

    return NULL;
}
