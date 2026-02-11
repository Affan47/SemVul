update_cutoff(struct csa *csa, glp_prob *lp,
                            double zstar, int cutoff_row,
                            double rel_impr)

{


    double cutoff;
    zstar -= csa->true_obj[0];
    if (csa->dir == GLP_MIN) {
        cutoff = zstar - compute_delta(csa, zstar, rel_impr);
        glp_set_row_bnds(lp, cutoff_row, GLP_UP, cutoff, cutoff);
    }
    else {
        cutoff = zstar + compute_delta(csa, zstar, rel_impr);
        glp_set_row_bnds(lp, cutoff_row, GLP_LO, cutoff, cutoff);
    }

    return cutoff;
}
