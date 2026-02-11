toggleEditButtons()
{
    if ( !layoutListWidget->currentItem() ) {
        deleteLayoutButton->setEnabled( 0 );
        renameLayoutButton->setEnabled( 0 );
    } else if( LayoutManager::instance()->isDefaultLayout( layoutListWidget->currentItem()->text() ) ) {
        deleteLayoutButton->setEnabled( 0 );
        renameLayoutButton->setEnabled( 0 );
    } else {
        deleteLayoutButton->setEnabled( 1 );
        renameLayoutButton->setEnabled( 1 );
    }
}
