WriteLTPPredictorData(CoderInfo *coderInfo, BitStream *bitStream, int writeFlag)
{
    int i, last_band;
    int bits;
    LtpInfo *ltpInfo = &coderInfo->ltpInfo;

    bits = 0;

    if (ltpInfo->global_pred_flag)
    {

        if(writeFlag)
            PutBit(bitStream, 1, 1);
        bits++;

        switch(coderInfo->block_type)
        {
        case ONLY_LONG_WINDOW:
        case LONG_SHORT_WINDOW:
        case SHORT_LONG_WINDOW:
            bits += LEN_LTP_LAG;
            bits += LEN_LTP_COEF;
            if(writeFlag)
            {
                PutBit(bitStream, ltpInfo->delay[0], LEN_LTP_LAG);
                PutBit(bitStream, ltpInfo->weight_idx,  LEN_LTP_COEF);
            }

            last_band = ((coderInfo->nr_of_sfb < MAX_LT_PRED_LONG_SFB) ?
                coderInfo->nr_of_sfb : MAX_LT_PRED_LONG_SFB);


            bits += last_band;
            if(writeFlag)
                for (i = 0; i < last_band; i++)
                    PutBit(bitStream, ltpInfo->sfb_prediction_used[i], LEN_LTP_LONG_USED);
            break;

        default:
            break;
        }
    }

    return (bits);
}
