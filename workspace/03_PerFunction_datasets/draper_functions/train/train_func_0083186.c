activate()
{
    DEBUG_BLOCK
    if ( parentList() )
        parentList()->setActiveCategory( this );
}
