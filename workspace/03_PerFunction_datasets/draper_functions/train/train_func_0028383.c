parsePointAttenuation(String& params, MaterialScriptContext& context)
    {
        StringVector vecparams = StringUtil::split(params, " \t");
        if (vecparams.size() != 1 && vecparams.size() != 4)
        {
            logParseError("Bad point_size_attenuation attribute, 1 or 4 parameters expected", context);
            return false;
        }
        if (vecparams[0] == "off")
        {
            context.pass->setPointAttenuation(false);
        }
        else if (vecparams[0] == "on")
        {
            if (vecparams.size() == 4)
            {
                context.pass->setPointAttenuation(true,
                    StringConverter::parseReal(vecparams[1]),
                    StringConverter::parseReal(vecparams[2]),
                    StringConverter::parseReal(vecparams[3]));
            }
            else
            {
                context.pass->setPointAttenuation(true);
            }
        }

        return false;
    }
