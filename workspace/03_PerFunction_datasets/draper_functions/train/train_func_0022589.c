sg_EditServers()
{
    int i;


    uMenu edit_menu(sg_GetBookmarkString( "menu_edit" ) );


    gServerFavoriteMenuEntries * entries[ NUM_FAVORITES ];
    for ( i = NUM_FAVORITES-1; i>=0; --i )
        entries[i] = tNEW( gServerFavoriteMenuEntries )( sg_holder->GetFavorite(i), edit_menu );


    edit_menu.Enter();


    for ( i = NUM_FAVORITES-1; i>=0; --i )
        delete entries[i];


    sg_GenerateConnectionItems();
}
