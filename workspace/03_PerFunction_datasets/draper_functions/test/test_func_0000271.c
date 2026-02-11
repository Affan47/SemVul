_getBlendFlags(SceneBlendType type, SceneBlendFactor& source, SceneBlendFactor& dest)
    {
        switch ( type )
        {
        case SBT_TRANSPARENT_ALPHA:
            source = SBF_SOURCE_ALPHA;
            dest = SBF_ONE_MINUS_SOURCE_ALPHA;
            return;
        case SBT_TRANSPARENT_COLOUR:
            source = SBF_SOURCE_COLOUR;
            dest = SBF_ONE_MINUS_SOURCE_COLOUR;
            return;
        case SBT_MODULATE:
            source = SBF_DEST_COLOUR;
            dest = SBF_ZERO;
            return;
        case SBT_ADD:
            source = SBF_ONE;
            dest = SBF_ONE;
            return;
        case SBT_REPLACE:
            source = SBF_ONE;
            dest = SBF_ZERO;
            return;
        }


        source = SBF_ONE;
        dest = SBF_ZERO;
    }
