DetectInpInchiCreationOptions ( InpInChI *pOneInput, int *bHasReconnected, int *bHasMetal,
                                             int *bHasFixedH, int *nModeFlagsStereo, int *bTautFlagsStereo )
{
    int ret=0, bHasStereo;
    int nModeFlagsValue=0, bTautFlagsValue;
    int iInChI, iMobileH, bIso, k, max_components, num_components;
    INChI *pInChI;
    int num_known_SB ;
    int num_known_SC ;
    int num_unk_und_SB, num_unk_und_SC;
    int num_SC_PIII, num_SC_AsIII;

    *bHasReconnected = *bHasFixedH = *nModeFlagsStereo = *bTautFlagsStereo = 0;
    nModeFlagsValue = bTautFlagsValue = bHasStereo = 0;
    num_known_SB = num_known_SC = num_unk_und_SB = num_unk_und_SC = num_SC_PIII = num_SC_AsIII = 0;
    *bHasMetal = 0;

    for ( iInChI   = 0; iInChI   < INCHI_NUM; iInChI ++   )
    {
        for ( iMobileH = 0; iMobileH < TAUT_NUM;  iMobileH ++ )
        {
            for ( bIso = 1; !nModeFlagsValue && 0 <= bIso; bIso -- )
            {
                switch( pOneInput->s[iInChI][iMobileH][bIso] )
                {
                case 1:
                    nModeFlagsValue |= REQ_MODE_STEREO | REQ_MODE_ISO_STEREO;
                    break;
                case 2:
                    nModeFlagsValue |= REQ_MODE_STEREO | REQ_MODE_ISO_STEREO | REQ_MODE_RELATIVE_STEREO;
                    break;
                case 3:
                    nModeFlagsValue |= REQ_MODE_STEREO | REQ_MODE_ISO_STEREO | REQ_MODE_RACEMIC_STEREO;
                }
            }

            max_components = pOneInput->pInpInChI[iInChI][iMobileH]?
                             pOneInput->nNumComponents[iInChI][iMobileH] : 0;

            for ( k = num_components = 0; k < max_components; k ++ )
            {
                pInChI = pOneInput->pInpInChI[iInChI][iMobileH] + k;
                ret = CountStereoTypes(pInChI,
                                       &num_known_SB, &num_known_SC,
                                       &num_unk_und_SB, &num_unk_und_SC,
                                       &num_SC_PIII, &num_SC_AsIII);
                if ( ret < 0 )
                {
                    return ret;
                }
                bHasStereo     += (ret == 2);
                if ( (ret > 0) )
                {

                    num_components ++;
                    *bHasReconnected |= ( iInChI   == INCHI_REC );
                    *bHasFixedH      |= ( iMobileH == TAUT_NON  );
                }
                *bHasMetal |= bInChIHasReconnectedMetal( pInChI );
            }
        }
    }

    if ( (nModeFlagsValue & REQ_MODE_RELATIVE_STEREO) && (nModeFlagsValue & REQ_MODE_RACEMIC_STEREO) )
    {
        return RI_ERR_SYNTAX;
    }
    if ( bHasStereo && !nModeFlagsValue )
    {

        nModeFlagsValue = REQ_MODE_STEREO | REQ_MODE_ISO_STEREO;
    }

    if ( !num_known_SB && num_unk_und_SB )
    {
        ;
    } else
    {
        nModeFlagsValue |= REQ_MODE_SB_IGN_ALL_UU;
    }

    if ( !num_known_SC && num_unk_und_SC )
    {
        ;
    } else
    {
        nModeFlagsValue |= REQ_MODE_SC_IGN_ALL_UU;
    }


    if ( num_SC_PIII )
    {
        bTautFlagsValue |= TG_FLAG_PHOSPHINE_STEREO;
    }

    if ( num_SC_AsIII )
    {
        bTautFlagsValue |= TG_FLAG_ARSINE_STEREO;
    }

    *nModeFlagsStereo = nModeFlagsValue;
    *bTautFlagsStereo = bTautFlagsValue;

    return 0;
}
