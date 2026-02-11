unparseDerivation(const Derivation & drv)
{
    string s;
    s.reserve(65536);
    s += "Derive([";

    bool first = true;
    foreach (DerivationOutputs::const_iterator, i, drv.outputs) {
        if (first) first = false; else s += ',';
        s += '('; printString(s, i->first);
        s += ','; printString(s, i->second.path);
        s += ','; printString(s, i->second.hashAlgo);
        s += ','; printString(s, i->second.hash);
        s += ')';
    }

    s += "],[";
    first = true;
    foreach (DerivationInputs::const_iterator, i, drv.inputDrvs) {
        if (first) first = false; else s += ',';
        s += '('; printString(s, i->first);
        s += ','; printStrings(s, i->second.begin(), i->second.end());
        s += ')';
    }

    s += "],";
    printStrings(s, drv.inputSrcs.begin(), drv.inputSrcs.end());

    s += ','; printString(s, drv.platform);
    s += ','; printString(s, drv.builder);
    s += ','; printStrings(s, drv.args.begin(), drv.args.end());

    s += ",[";
    first = true;
    foreach (StringPairs::const_iterator, i, drv.env) {
        if (first) first = false; else s += ',';
        s += '('; printString(s, i->first);
        s += ','; printString(s, i->second);
        s += ')';
    }

    s += "])";

    return s;
}
