showRemoveDialog( const Meta::TrackList &tracks )
{
    DEBUG_BLOCK
    if( !isHidingRemoveConfirm() )
    {
        Collections::CollectionLocationDelegate *delegate = Amarok::Components::collectionLocationDelegate();
        const bool del = delegate->reallyDelete( this, tracks );

        if( !del )
            abort();
        else
            slotShowRemoveDialogDone();
    } else
        slotShowRemoveDialogDone();
}
