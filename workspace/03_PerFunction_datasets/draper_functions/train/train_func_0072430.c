clean_slopes(){
    int i;
    if (slopes) {
        for (i=0;i<di_resolution*di_max_dist;i++) {
            delete slopes[i]; slopes[i] = 0;
            delete curves[i]; curves[i] = 0;
            delete infs[i]; infs[i] = 0;
        }
    }
    akt_slopes = 0;
    akt_curves = 0;
    akt_infs = 0;
}
