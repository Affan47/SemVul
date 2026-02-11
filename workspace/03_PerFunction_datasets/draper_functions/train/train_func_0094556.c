get_default_motions( const int id_ )
{
    int id = id_;
    if( id == CONTROL::CancelMosaic ) id = CONTROL::CancelMosaicButton;

    return MouseKeyConf::get_default_motions( id );
}
