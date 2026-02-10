initValue(GraphView const *gv, unsigned int chain)
{
    double const *x = gv->nodes()[0]->value(chain);
    unsigned int N = gv->nodes()[0]->length();
    vector<double> ivalue(N);
    for (unsigned int i = 0; i < N; ++i) {
	ivalue[i] = x[i];
    }
    return ivalue;
}
