parseWaveXform(String& params, MaterialScriptContext& context)
    {
        StringUtil::toLowerCase(params);
        StringVector vecparams = StringUtil::split(params, " \t");

        if (vecparams.size() != 6)
        {
            logParseError("Bad wave_xform attribute, wrong number of parameters "
                "(expected 6)", context);
            return false;
        }
        TextureUnitState::TextureTransformType ttype;
        WaveformType waveType;

        if (vecparams[0]=="scroll_x")
            ttype = TextureUnitState::TT_TRANSLATE_U;
        else if (vecparams[0]=="scroll_y")
            ttype = TextureUnitState::TT_TRANSLATE_V;
        else if (vecparams[0]=="rotate")
            ttype = TextureUnitState::TT_ROTATE;
        else if (vecparams[0]=="scale_x")
            ttype = TextureUnitState::TT_SCALE_U;
        else if (vecparams[0]=="scale_y")
            ttype = TextureUnitState::TT_SCALE_V;
        else
        {
            logParseError("Bad wave_xform attribute, parameter 1 must be 'scroll_x', "
                "'scroll_y', 'rotate', 'scale_x' or 'scale_y'", context);
            return false;
        }

        if (vecparams[1]=="sine")
            waveType = WFT_SINE;
        else if (vecparams[1]=="triangle")
            waveType = WFT_TRIANGLE;
        else if (vecparams[1]=="square")
            waveType = WFT_SQUARE;
        else if (vecparams[1]=="sawtooth")
            waveType = WFT_SAWTOOTH;
        else if (vecparams[1]=="inverse_sawtooth")
            waveType = WFT_INVERSE_SAWTOOTH;
        else
        {
            logParseError("Bad wave_xform attribute, parameter 2 must be 'sine', "
                "'triangle', 'square', 'sawtooth' or 'inverse_sawtooth'", context);
            return false;
        }

        context.textureUnit->setTransformAnimation(
            ttype,
            waveType,
            StringConverter::parseReal(vecparams[2]),
            StringConverter::parseReal(vecparams[3]),
            StringConverter::parseReal(vecparams[4]),
            StringConverter::parseReal(vecparams[5]) );

        return false;
    }
