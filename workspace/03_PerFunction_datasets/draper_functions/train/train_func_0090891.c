parseTextureCustomParameter(String& params, MaterialScriptContext& context)
    {


        StringVector vecparams = StringUtil::split(params, " \t", 1);
        if (vecparams.size() != 2)
        {
            logParseError("Invalid texture parameter entry; "
                "there must be a parameter name and at least one value.",
                context);
            return false;
        }

        if( ExternalTextureSourceManager::getSingleton().getCurrentPlugIn() != 0 )

            ExternalTextureSourceManager::getSingleton().getCurrentPlugIn()->setParameter( vecparams[0], vecparams[1] );

        return false;
    }
