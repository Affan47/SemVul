init( AxisAlignedBox &box, int depth )
{

    if ( mOctree != 0 )
        OGRE_DELETE mOctree;

    mOctree = OGRE_NEW Octree( 0 );

    mMaxDepth = depth;
    mBox = box;

    mOctree -> mBox = box;

    Vector3 min = box.getMinimum();

    Vector3 max = box.getMaximum();

    mOctree -> mHalfSize = ( max - min ) / 2;


    mShowBoxes = false;

    mNumObjects = 0;

    Vector3 v( 1.5, 1.5, 1.5 );

    mScaleFactor.setScale( v );


}
