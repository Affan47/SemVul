initDefaults(const String& t)
    {


        mDirection = Vector3::UNIT_Z;
        mUp = Vector3::UNIT_Y;
        setSize(100,100,100);
        mType = t;


        if (createParamDictionary(mType + "Emitter"))
        {

            addBaseParameters();
            ParamDictionary* dict = getParamDictionary();


            dict->addParameter(ParameterDef("width",
                "Width of the shape in world coordinates.",
                PT_REAL),&msWidthCmd);
            dict->addParameter(ParameterDef("height",
                "Height of the shape in world coordinates.",
                PT_REAL),&msHeightCmd);
            dict->addParameter(ParameterDef("depth",
                "Depth of the shape in world coordinates.",
                PT_REAL),&msDepthCmd);
            return true;

        }
        return false;
    }
