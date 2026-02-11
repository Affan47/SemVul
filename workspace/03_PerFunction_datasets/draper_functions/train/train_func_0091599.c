_defragmentBatch( bool optimizeCulling, InstancedEntityVec &usedEntities,
                                            CustomParamsVec &usedParams )
    {

        mInstancedEntities.clear();
        mCustomParams.clear();
        deleteUnusedInstancedEntities();

        if( !optimizeCulling )
            defragmentBatchNoCull( usedEntities, usedParams );
        else
            defragmentBatchDoCull( usedEntities, usedParams );


        uint32 instanceId = 0;
        InstancedEntityVec::const_iterator itor = mInstancedEntities.begin();
        InstancedEntityVec::const_iterator end  = mInstancedEntities.end();

        while( itor != end )
        {
            (*itor)->mInstanceId = instanceId++;
            (*itor)->mBatchOwner = this;
            ++itor;
        }


        assert( (signed)(mInstancesPerBatch) - (signed)(mInstancedEntities.size()) >= 0 );
        mInstancedEntities.reserve( mInstancesPerBatch );
        mUnusedEntities.reserve( mInstancesPerBatch );
        mCustomParams.reserve( mCreator->getNumCustomParams() * mInstancesPerBatch );
        for( size_t i=mInstancedEntities.size(); i<mInstancesPerBatch; ++i )
        {
            InstancedEntity *instance = generateInstancedEntity(i);
            mInstancedEntities.push_back( instance );
            mUnusedEntities.push_back( instance );
            mCustomParams.push_back( Ogre::Vector4::ZERO );
        }


        if( !isBatchUnused() )
            _boundsDirty();
    }
