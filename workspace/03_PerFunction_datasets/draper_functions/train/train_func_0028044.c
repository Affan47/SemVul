edit_delete( Edit **edit )
{
    if ( *edit ) {
        label_delete( &(*edit)->label );
        if ( (*edit)->text ) free( (*edit)->text );
        free( *edit ); *edit = 0;
    }
}
