getNextFreeTextureCoordinate() const
    {
        unsigned short texCoord = 0;
        for (VertexElementList::const_iterator i = mElementList.begin();
             i != mElementList.end(); ++i)
        {
            const VertexElement& el = *i;
            if (el.getSemantic() == VES_TEXTURE_COORDINATES)
            {
                ++texCoord;
            }
        }
        return texCoord;
    }
