setLayout( const QString &layoutName )
{
    DEBUG_BLOCK
    m_layoutName = layoutName;

    if( m_layoutsMap->keys().contains( layoutName ) )
    {
        debug() << "loaded layout";
        PlaylistLayout layout = m_layoutsMap->value( layoutName );
        for( int part = 0; part < PlaylistLayout::NumParts; part++ )
            m_partsEdit[part]->readLayout( layout.layoutForPart( (PlaylistLayout::Part)part ) );
        inlineControlsChekbox->setChecked( layout.inlineControls() );
        tooltipsCheckbox->setChecked( layout.tooltips() );
        groupByComboBox->setCurrentIndex( groupByComboBox->findData( layout.groupBy() ) );

        setEnabledTabs();


        debug() << "not dirty anyway!!";
        (*m_layoutsMap)[m_layoutName].setDirty( false );
    }
    else
    {
        for( int part = 0; part < PlaylistLayout::NumParts; part++ )
            m_partsEdit[part]->clear();
    }
}
