parseIteration(String& params, MaterialScriptContext& context)
    {


        StringUtil::toLowerCase(params);
        StringVector vecparams = StringUtil::split(params, " \t");
        if (vecparams.size() < 1 || vecparams.size() > 4)
        {
            logParseError("Bad iteration attribute, expected 1 to 3 parameters.", context);
            return false;
        }

        if (vecparams[0]=="once")
            context.pass->setIteratePerLight(false, false);
        else if (vecparams[0]=="once_per_light")
        {
            if (vecparams.size() == 2)
            {
                parseIterationLightTypes(vecparams[1], context);
            }
            else
            {
                context.pass->setIteratePerLight(true, false);
            }

        }
        else
        {
            int passIterationCount = StringConverter::parseInt(vecparams[0]);
            if (passIterationCount > 0)
            {
                context.pass->setPassIterationCount(passIterationCount);
                if (vecparams.size() > 1)
                {
                    if (vecparams[1] == "per_light")
                    {
                        if (vecparams.size() == 3)
                        {
                            parseIterationLightTypes(vecparams[2], context);
                        }
                        else
                        {
                            context.pass->setIteratePerLight(true, false);
                        }
                    }
                    else if (vecparams[1] == "per_n_lights")
                    {
                        if (vecparams.size() < 3)
                        {
                            logParseError(
                                "Bad iteration attribute, expected number of lights.",
                                context);
                        }
                        else
                        {

                            context.pass->setLightCountPerIteration(
                                (ushort)StringConverter::parseInt(vecparams[2]));

                            if (vecparams.size() == 4)
                            {
                                parseIterationLightTypes(vecparams[3], context);
                            }
                            else
                            {
                                context.pass->setIteratePerLight(true, false);
                            }
                        }
                    }
                    else
                        logParseError(
                            "Bad iteration attribute, valid parameters are <number> [per_light|per_n_lights <num_lights>] [light type].", context);
                }
            }
            else
                logParseError(
                    "Bad iteration attribute, valid parameters are 'once' or 'once_per_light' or <number> [per_light|per_n_lights <num_lights>] [light type].", context);
        }
        return false;
    }
