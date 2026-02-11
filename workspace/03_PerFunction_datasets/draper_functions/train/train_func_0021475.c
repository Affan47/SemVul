amdlibCopyPhotFrom(amdlibPHOTOMETRY *dstPhot,
                                    amdlibPHOTOMETRY *srcPhot,
                                    int              index,
                                    int              nbOfElem,
                                    amdlibERROR_MSG  errMsg)
{
    int i, j;
    amdlibLogTrace("amdlibCopyPhotFrom()");

    if ((dstPhot->thisPtr == NULL) && (index != 0))
    {
        amdlibSetErrMsg("Could not copy non-initialized data from index %d",
                        index);
        return amdlibFAILURE;
    }

    if (srcPhot->thisPtr == NULL)
    {

        return amdlibSUCCESS;
    }

    if (index == 0)
    {
        for (i=0; i < srcPhot->nbFrames * srcPhot->nbBases; i++)
        {
            for (j=0; j < srcPhot->nbWlen; j++)
            {
                dstPhot->table[i].fluxSumPiPj[j] =
                    srcPhot->table[i].fluxSumPiPj[j];
                dstPhot->table[i].sigma2FluxSumPiPj[j] =
                    srcPhot->table[i].sigma2FluxSumPiPj[j];
                dstPhot->table[i].fluxRatPiPj[j] =
                    srcPhot->table[i].fluxRatPiPj[j];
                dstPhot->table[i].sigma2FluxRatPiPj[j] =
                    srcPhot->table[i].sigma2FluxRatPiPj[j];
                dstPhot->table[i].PiMultPj[j] =
                    srcPhot->table[i].PiMultPj[j];
            }
        }
    }
    else
    {
        if (dstPhot->nbFrames != srcPhot->nbFrames)
        {
            amdlibSetErrMsg("Different number of frames! (%d and %d)",
                            dstPhot->nbFrames, srcPhot->nbFrames);
            return amdlibFAILURE;
        }
        if (dstPhot->nbBases != srcPhot->nbBases)
        {
            amdlibSetErrMsg("Different of bases (%d and %d)",
                            dstPhot->nbBases, srcPhot->nbBases);
            return amdlibFAILURE;
        }
        for (i=0; i < srcPhot->nbFrames * srcPhot->nbBases; i++)
        {
            for (j = 0; j < nbOfElem; j++)
            {
                dstPhot->table[i].fluxSumPiPj[index+j] =
                    srcPhot->table[i].fluxSumPiPj[j];

                dstPhot->table[i].sigma2FluxSumPiPj[index+j] =
                    srcPhot->table[i].sigma2FluxSumPiPj[j];

                dstPhot->table[i].fluxRatPiPj[index+j] =
                    srcPhot->table[i].fluxRatPiPj[j];

                dstPhot->table[i].sigma2FluxRatPiPj[index+j] =
                    srcPhot->table[i].sigma2FluxRatPiPj[j];

                dstPhot->table[i].PiMultPj[index+j] =
                    srcPhot->table[i].PiMultPj[j];
            }
        }
    }
    return amdlibSUCCESS;
}
