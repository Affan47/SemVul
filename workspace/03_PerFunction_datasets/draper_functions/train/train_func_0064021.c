setExpansionY(double val) {
    double exp_y = expansionY();
    if(!are_near(exp_y, 0.0)) {
        double coef = val / expansionY();
        for(unsigned i=2; i<4; i++) _c[i] *= coef;
    }
}
