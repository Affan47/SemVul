parseAlphaOpEx(String& params, MaterialScriptContext& context)
    {
        StringUtil::toLowerCase(params);
        StringVector vecparams = StringUtil::split(params, " \t");
        size_t numParams = vecparams.size();
        if (numParams < 3 || numParams > 6)
        {
            logParseError("Bad alpha_op_ex attribute, wrong number of parameters "
                "(expected 3 to 6)", context);
            return false;
        }
        LayerBlendOperationEx op;
        LayerBlendSource src1, src2;
        Real manual = 0.0;
        Real arg1 = 1.0, arg2 = 1.0;

        try {
            op = convertBlendOpEx(vecparams[0]);
            src1 = convertBlendSource(vecparams[1]);
            src2 = convertBlendSource(vecparams[2]);
            if (op == LBX_BLEND_MANUAL)
            {
                if (numParams != 4)
                {
                    logParseError("Bad alpha_op_ex attribute, wrong number of parameters "
                        "(expected 4 for manual blend)", context);
                    return false;
                }
                manual = StringConverter::parseReal(vecparams[3]);
            }
            if (src1 == LBS_MANUAL)
            {
                unsigned int parIndex = 3;
                if (op == LBX_BLEND_MANUAL)
                    parIndex++;

                if (numParams < parIndex)
                {
                    logParseError(
                        "Bad alpha_op_ex attribute, wrong number of parameters (expected " +
                        StringConverter::toString(parIndex - 1) + ")", context);
                    return false;
                }

                arg1 = StringConverter::parseReal(vecparams[parIndex]);
            }

            if (src2 == LBS_MANUAL)
            {
                unsigned int parIndex = 3;
                if (op == LBX_BLEND_MANUAL)
                    parIndex++;
                if (src1 == LBS_MANUAL)
                    parIndex++;

                if (numParams < parIndex)
                {
                    logParseError(
                        "Bad alpha_op_ex attribute, wrong number of parameters "
                        "(expected " + StringConverter::toString(parIndex - 1) + ")", context);
                    return false;
                }

                arg2 = StringConverter::parseReal(vecparams[parIndex]);
            }
        }
        catch (Exception& e)
        {
            logParseError("Bad alpha_op_ex attribute, " + e.getDescription(), context);
            return false;
        }

        context.textureUnit->setAlphaOperation(op, src1, src2, arg1, arg2, manual);
        return false;
    }
