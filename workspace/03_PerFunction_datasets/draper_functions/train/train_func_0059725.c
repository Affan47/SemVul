swabHorAcc16(TIFF* tif, tidata_t cp0, tsize_t cc)
{
        tsize_t stride = PredictorState(tif)->stride;
        uint16* wp = (uint16*) cp0;
        tsize_t wc = cc / 2;

        if (wc > stride) {
                TIFFSwabArrayOfShort(wp, wc);
                wc -= stride;
                do {
                        REPEAT4(stride, wp[stride] += wp[0]; wp++)
                        wc -= stride;
                } while ((int32) wc > 0);
        }
}
