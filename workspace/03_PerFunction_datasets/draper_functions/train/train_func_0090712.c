setOption( const String & key, const void * val )
{
    if ( key == "Size" )
    {
        resize( * static_cast < const AxisAlignedBox * > ( val ) );
        return true;
    }

    else if ( key == "Depth" )
    {
        mMaxDepth = * static_cast < const int * > ( val );

        AxisAlignedBox box = mOctree->mBox;
        resize(box);
        return true;
    }

    else if ( key == "ShowOctree" )
    {
        mShowBoxes = * static_cast < const bool * > ( val );
        return true;
    }


    return SceneManager::setOption( key, val );


}
