parseParamNamedAuto(String& params, MaterialScriptContext& context)
    {

        if (context.program.isNull() || !context.program->isSupported())
        {
            return false;
        }

        StringVector vecparams = StringUtil::split(params, " \t");
        if (vecparams.size() != 2 && vecparams.size() != 3)
        {
            logParseError("Invalid param_indexed_auto attribute - expected 2 or 3 parameters.",
                context);
            return false;
        }


        try {
            const GpuConstantDefinition& def =
                context.programParams->getConstantDefinition(vecparams[0]);
            (void)def;
        }
        catch (Exception& e)
        {
            logParseError("Invalid param_named_auto attribute - " + e.getDescription(), context);
            return false;
        }

        processAutoProgramParam(true, "param_named_auto", vecparams, context, 0, vecparams[0]);

        return false;
    }
