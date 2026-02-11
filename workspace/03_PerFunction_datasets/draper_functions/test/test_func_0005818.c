setupVertexDeclaration(void)
    {
        if (mVertexDeclDirty)
        {
            VertexDeclaration* decl = mVertexData->vertexDeclaration;
            decl->removeAllElements();

            size_t offset = 0;

            decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
            offset += VertexElement::getTypeSize(VET_FLOAT3);

            if (mUseVertexColour)
            {
                decl->addElement(0, offset, VET_COLOUR, VES_DIFFUSE);
                offset += VertexElement::getTypeSize(VET_COLOUR);
            }

            if (mUseTexCoords)
            {
                decl->addElement(0, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
            }

            if (!mUseTexCoords && !mUseVertexColour)
            {
                LogManager::getSingleton().logMessage(
                    "Error - BillboardChain '" + mName + "' is using neither "
                    "texture coordinates or vertex colours; it will not be "
                    "visible on some rendering APIs so you should change this "
                    "so you use one or the other.");
            }
            mVertexDeclDirty = false;
        }
    }
