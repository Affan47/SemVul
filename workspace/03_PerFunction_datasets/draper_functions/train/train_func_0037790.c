theme_delete_list()
{
    int i;
    if ( theme_names ) {
        for ( i = 0; i < theme_count; i++ )
            if ( theme_names[i] ) free( theme_names[i] );
        free( theme_names );
        theme_names = 0;
    }
}
