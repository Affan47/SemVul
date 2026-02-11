calculateMaxNumInstances(
                    const SubMesh *baseSubMesh, uint16 flags ) const
    {
        size_t retVal = 0;

        RenderSystem *renderSystem = Root::getSingleton().getRenderSystem();
        const RenderSystemCapabilities *capabilities = renderSystem->getCapabilities();


        if( capabilities->hasCapability( RSC_VERTEX_TEXTURE_FETCH ) )
        {

            const size_t numBones = std::max<size_t>( 1, baseSubMesh->blendIndexToBoneIndexMap.size() );
            retVal = c_maxTexWidth * c_maxTexHeight / mRowLength / numBones;

            if( flags & IM_USE16BIT )
            {
                if( baseSubMesh->vertexData->vertexCount * retVal > 0xFFFF )
                    retVal = 0xFFFF / baseSubMesh->vertexData->vertexCount;
            }

            if( flags & IM_VTFBESTFIT )
            {
                const size_t instancesPerBatch = std::min( retVal, mInstancesPerBatch );

                const size_t numWorldMatrices = instancesPerBatch * numBones;

                size_t texWidth  = std::min<size_t>( numWorldMatrices * mRowLength, c_maxTexWidth );
                size_t texHeight = numWorldMatrices * mRowLength / c_maxTexWidth;

                const size_t remainder = (numWorldMatrices * mRowLength) % c_maxTexWidth;

                if( remainder && texHeight > 0 )
                    retVal = static_cast<size_t>(texWidth * texHeight / (float)mRowLength / (float)(numBones));
            }
        }

        return retVal;

    }
