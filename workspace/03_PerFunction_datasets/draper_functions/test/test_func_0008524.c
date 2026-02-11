pushMultiClosureDefs(Tree ldefs, Tree visited, Tree lenv)
{
    Tree lenv2 = pushNewLayer(lenv);
    while (!isNil(ldefs)) {
        Tree def = hd(ldefs);
        Tree id = hd(def);
        Tree rhs= tl(def);
        Tree cl = closure(tl(def),nil,visited,lenv2);
        stringstream s; s << boxpp(id);
        if (!isBoxCase(rhs)) setDefNameProperty(cl,s.str());
        addLayerDef( id, cl, lenv2 );
        ldefs = tl(ldefs);
    }
    return lenv2;
}
