_initialise(bool forceReinitialise)
    {
        if (forceReinitialise)
            _deinitialise();

        if (mInitialised)
            return;

        if (mMesh->isBackgroundLoaded() && !mMesh->isLoaded())
        {


            mMesh->addListener(this);
        }


        mMesh->load();


        if (!mMesh->isLoaded())
            return;


        if (mMesh->hasSkeleton() && !mMesh->getSkeleton().isNull())
        {
            mSkeletonInstance = OGRE_NEW SkeletonInstance(mMesh->getSkeleton());
            mSkeletonInstance->load();

            if ( mUpdateBoundingBoxFromSkeleton && mMesh->getBoneBoundingRadius() == Real(0))
            {
                mMesh->_computeBoneBoundingRadius();
            }
        }


        buildSubEntityList(mMesh, &mSubEntityList);
#if !OGRE_NO_MESHLOD

        if (mMesh->hasManualLodLevel())
        {
            ushort i, numLod;
            numLod = mMesh->getNumLodLevels();

            for (i = 1; i < numLod; ++i)
            {
                const MeshLodUsage& usage = mMesh->getLodLevel(i);
                Entity* lodEnt;
                if(!usage.manualName.empty()){

                    OgreAssert(usage.manualMesh->getNumLodLevels() == 1, "Manual Lod Mesh can't have Lod levels!");

                    if(usage.manualMesh->getNumLodLevels() != 1) {

                        usage.manualMesh->removeLodLevels();
                    }


                    lodEnt = OGRE_NEW Entity(mName + "Lod" + StringConverter::toString(i),
                        usage.manualMesh);
                } else {

                    lodEnt = this;
                }
                mLodEntityList.push_back(lodEnt);
            }
        }
#endif


        if (hasSkeleton())
        {
            mFrameBonesLastUpdated = OGRE_NEW_T(unsigned long, MEMCATEGORY_ANIMATION)(std::numeric_limits<unsigned long>::max());
            mNumBoneMatrices = mSkeletonInstance->getNumBones();
            mBoneMatrices = static_cast<Matrix4*>(OGRE_MALLOC_SIMD(sizeof(Matrix4) * mNumBoneMatrices, MEMCATEGORY_ANIMATION));
        }
        if (hasSkeleton() || hasVertexAnimation())
        {
            mAnimationState = OGRE_NEW AnimationStateSet();
            mMesh->_initAnimationState(mAnimationState);
            prepareTempBlendBuffers();
        }

        reevaluateVertexProcessing();


        if( mParentNode )
        {
            getParentSceneNode()->needUpdate();
        }

        mInitialised = true;
        mMeshStateCount = mMesh->getStateCount();
    }
