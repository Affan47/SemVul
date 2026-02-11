get_normalizing_factor(int gc, double *gc_meds, GCBinParams *params) {
    int x = gc - params->min_gc;
    if (x < params->left_edge_bin_size + params->bin_size / 2) {
        double rise  = gc_meds[1] - gc_meds[0];
        double  run  =   (double) params->left_edge_bin_size / 2.0
                       + (double) params->bin_size / 2.0;
        double slope = rise / run;
        return gc_meds[0] + slope * ((double) x - params->left_edge_center);
    } else if (x > params->gc_range - (params->right_edge_bin_size + params->bin_size / 2)) {
        double rise  = gc_meds[params->n_bins-2] - gc_meds[params->n_bins-1];
        double  run  =   (double) params->right_edge_bin_size / 2.0
                       + (double) params->bin_size / 2.0;
        double slope = rise / run;
        return gc_meds[params->n_bins-1] + slope * (params->right_edge_center - (double) x);
    } else {
        x -= params->left_edge_bin_size;
        int bin = 1 + x / params->bin_size;
        int remainder = x % params->bin_size;
        if (params->bin_size_odd && remainder == params->bin_size / 2) {
            return gc_meds[bin];
        } else {
            double t = ((double) remainder + (double) (remainder+1)) / (2.0 * params->bin_size);
            if (t < 0.5) {
                bin--;
                t += 0.5;
            } else {
                t -= 0.5;
            }
            return (1.0 - t) * gc_meds[bin] + t * gc_meds[bin+1];
        }
    }
}
