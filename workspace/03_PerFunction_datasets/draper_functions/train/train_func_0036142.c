get_floor_average(vorbis_enc_floor * fc, float * coeffs, int i) {
    int begin = fc->list[fc->list[FFMAX(i-1, 0)].sort].x;
    int end   = fc->list[fc->list[FFMIN(i+1, fc->values - 1)].sort].x;
    int j;
    float average = 0;

    for (j = begin; j < end; j++)
        average += fabs(coeffs[j]);
    return average / (end - begin);
}
