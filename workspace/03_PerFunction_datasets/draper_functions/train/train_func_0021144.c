createInstanceImpl( const String& name,
        const NameValuePairList* params)
    {
        size_t maxElements = 20;
        size_t numberOfChains = 1;
        bool useTex = true;
        bool useCol = true;

        if (params != 0)
        {
            NameValuePairList::const_iterator ni = params->find("maxElements");
            if (ni != params->end())
            {
                maxElements = StringConverter::parseUnsignedLong(ni->second);
            }
            ni = params->find("numberOfChains");
            if (ni != params->end())
            {
                numberOfChains = StringConverter::parseUnsignedLong(ni->second);
            }
            ni = params->find("useTextureCoords");
            if (ni != params->end())
            {
                useTex = StringConverter::parseBool(ni->second);
            }
            ni = params->find("useVertexColours");
            if (ni != params->end())
            {
                useCol = StringConverter::parseBool(ni->second);
            }

        }

        return OGRE_NEW RibbonTrail(name, maxElements, numberOfChains, useTex, useCol);

    }
