sg_AlternativeMaster( int ID )
{

    std::stringstream suffix;
    suffix << "_" << ID;


    gServerFavorite & favorite = sg_masterHolder.GetFavorite(ID);
    gServerInfoFavorite fav( favorite.address_, favorite.port_ );


    gServerBrowser::BrowseSpecialMaster( &fav, suffix.str().c_str() );
}
