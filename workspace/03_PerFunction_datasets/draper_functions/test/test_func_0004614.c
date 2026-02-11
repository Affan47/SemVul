addExtension( ExtensionInterface* ext )
{
    m_extensions.append( ext );

    ext->setOwner( this );

    ui.pageStack->addWidget( ext->settingsPane() );
    ui.pageList->addItem( ext->tabCaption() );

    int idx = ui.pageList->count() - 1;
    ui.pageList->item( idx )->setIcon( *ext->settingsIcon() );


    ui.pageList->item( idx )->setText( ext->tabCaption() );

    connect( ext,  SIGNAL( settingsChanged() ),
             this, SLOT( configChanged() ) );
}
