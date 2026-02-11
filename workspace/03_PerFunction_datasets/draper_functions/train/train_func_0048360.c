gainCompensateAndOverlap (float *pIn, float *pPrev, float *pOut, gain_info *pGain1, gain_info *pGain2)
{

    float  gain1, gain2, gain_inc;
    int   cnt, numdata, nsample, startLoc, endLoc;


    if (pGain2->num_gain_data == 0)
        gain1 = 1.0;
    else
        gain1 = gain_tab1[pGain2->levcode[0]];

    if (pGain1->num_gain_data == 0) {
        for (cnt = 0; cnt < 256; cnt++)
            pOut[cnt] = pIn[cnt] * gain1 + pPrev[cnt];
    } else {
        numdata = pGain1->num_gain_data;
        pGain1->loccode[numdata] = 32;
        pGain1->levcode[numdata] = 4;

        nsample = 0;

        for (cnt = 0; cnt < numdata; cnt++) {
            startLoc = pGain1->loccode[cnt] * 8;
            endLoc = startLoc + 8;

            gain2 = gain_tab1[pGain1->levcode[cnt]];
            gain_inc = gain_tab2[(pGain1->levcode[cnt+1] - pGain1->levcode[cnt])+15];


            for (; nsample < startLoc; nsample++)
                pOut[nsample] = (pIn[nsample] * gain1 + pPrev[nsample]) * gain2;


            for (; nsample < endLoc; nsample++) {
                pOut[nsample] = (pIn[nsample] * gain1 + pPrev[nsample]) * gain2;
                gain2 *= gain_inc;
            }
        }

        for (; nsample < 256; nsample++)
            pOut[nsample] = (pIn[nsample] * gain1) + pPrev[nsample];
    }


    memcpy(pPrev, &pIn[256], 256*sizeof(float));
}
