removeBlendData()
    {
        VertexData *thisVertexData = mRenderOperation.vertexData;

        unsigned short safeSource = 0xFFFF;
        const VertexElement* blendIndexElem = thisVertexData->vertexDeclaration->findElementBySemantic(
                                                                                VES_BLEND_INDICES );
        if( blendIndexElem )
        {

            safeSource = blendIndexElem->getSource();

            thisVertexData->vertexBufferBinding->unsetBinding( blendIndexElem->getSource() );
        }

        const VertexElement* blendWeightElem = thisVertexData->vertexDeclaration->findElementBySemantic(
                                                                                VES_BLEND_WEIGHTS );
        if( blendWeightElem && blendWeightElem->getSource() != safeSource )
        {

            thisVertexData->vertexBufferBinding->unsetBinding( blendWeightElem->getSource() );
        }

        thisVertexData->vertexDeclaration->removeElement(VES_BLEND_INDICES);
        thisVertexData->vertexDeclaration->removeElement(VES_BLEND_WEIGHTS);
        thisVertexData->closeGapsInBindings();
    }
