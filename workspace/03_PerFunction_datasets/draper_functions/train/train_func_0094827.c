FDKaacEnc_getTotalConsumedDynBits(QC_OUT** qcOut,
                                   INT nSubFrames)
{
    INT c, totalBits=0;


    for (c=0; c<nSubFrames; c++)
    {


        if (qcOut[c]->usedDynBits==-1) return -1;
        totalBits += qcOut[c]->usedDynBits;
    }

    return totalBits;

}
