generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
{


    generateDelayLine(ctype, vname, mxd, exp);
    setVectorNameProperty(sig, vname);
    if (verySimple(sig)) {
        return exp;
    } else {
        return subst("$0[i]", vname);
    }
}
