amdlibUpdateSelection(amdlibSELECTION *selection)
{
    int band, frame, base;

    amdlibLogTrace("amdlibUpdateSelection()");


    for (band = 0; band < amdlibNB_BANDS; band++)
    {
        int nbFramesOkForClosure = 0;

        for (base = 0; base < selection->nbBases; base++)
        {
            selection->band[band].nbSelectedFrames[base]   = 0;
            selection->band[band].firstSelectedFrame[base] = -1;
            for (frame = 0; frame < selection->nbFrames; frame++)
            {
                if (selection->band[band].isSelectedPt[base][frame] ==
                                                                    amdlibTRUE)
                {
                    selection->band[band].nbSelectedFrames[base] += 1;
                    if (selection->band[band].firstSelectedFrame[base] == -1)
                    {
                        selection->band[band].firstSelectedFrame[base] = frame;
                    }
                }
            }
        }

        if (selection->nbBases == 3)
        {
            int frame;
            for (frame = 0; frame < selection->nbFrames; frame++)
            {
                if ((selection->band[band].isSelectedPt[0][frame] == amdlibTRUE) ||
                    (selection->band[band].isSelectedPt[1][frame] == amdlibTRUE) ||
                    (selection->band[band].isSelectedPt[2][frame] == amdlibTRUE)   )
                {
                    selection->band[band].frameOkForClosure[nbFramesOkForClosure] = frame;
                    nbFramesOkForClosure++;
                }
            }
        }
        selection->band[band].nbFramesOkForClosure = nbFramesOkForClosure;
    }
    return amdlibSUCCESS;
}
