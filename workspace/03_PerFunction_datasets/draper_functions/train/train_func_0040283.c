CreateLoopSubdivShape(const Transform *o2w, const Transform *w2o,
        bool reverseOrientation, const ParamSet &params) {
    int nlevels = params.FindOneInt("nlevels", 3);
    int nps, nIndices;
    const int *vi = params.FindInt("indices", &nIndices);
    const Point *P = params.FindPoint("P", &nps);
    if (!vi || !P) return NULL;


    string scheme = params.FindOneString("scheme", "loop");

    return new LoopSubdiv(o2w, w2o, reverseOrientation, nIndices/3, nps,
        vi, P, nlevels);
}
