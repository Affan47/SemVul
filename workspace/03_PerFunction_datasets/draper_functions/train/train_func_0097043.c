invertSelection()
{
    for ( KFileItem item = firstFileItem(); !item.isNull(); item = nextItem( item ) )
        setSelected( item, !isSelected( item ) );
}
