calCoef(double *coef, GraphView const *gv, unsigned int chain)
{


    const double xold = *gv->nodes()[0]->value(chain);
    vector<StochasticNode const*> const &schildren = gv->stochasticChildren();
    unsigned long nchildren = schildren.size();

    for (unsigned int i = 0; i < nchildren; ++i) {
        coef[i] = -getScale(schildren[i], chain);
    }
    double val = xold + 1;
    gv->setValue(&val, 1, chain);
    for (unsigned int i = 0; i < nchildren; ++i) {
        coef[i] += getScale(schildren[i], chain);
    }
    gv->setValue(&xold, 1, chain);
}
