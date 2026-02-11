precomputeAttributeDependenciesAux(DOM::DocumentImpl* doc, DOM::CSSSelector* sel, bool isAncestor, bool isSubject)
{
    if(sel->attrLocalName.id())
    {
        uint selAttr = makeId(sel->attrNamespace.id(), sel->attrLocalName.id());

        if (isSubject)
            doc->dynamicDomRestyler().addDependency(selAttr, PersonalDependency);
        else if (isAncestor)
            doc->dynamicDomRestyler().addDependency(selAttr, AncestorDependency);
        else
            doc->dynamicDomRestyler().addDependency(selAttr, PredecessorDependency);
    }
    if(sel->match == CSSSelector::PseudoClass)
    {
	switch (sel->pseudoType()) {
            case CSSSelector::PseudoNot:
                precomputeAttributeDependenciesAux(doc, sel->simpleSelector, isAncestor, true);
                break;
            default:
                break;
        }
    }
    CSSSelector::Relation relation = KDE_CAST_BF_ENUM(CSSSelector::Relation, sel->relation);
    sel = sel->tagHistory;
    if (!sel) return;

    switch(relation)
    {
    case CSSSelector::Descendant:
    case CSSSelector::Child:
        precomputeAttributeDependenciesAux(doc, sel, true, false);
        break;
    case CSSSelector::IndirectAdjacent:
    case CSSSelector::DirectAdjacent:
        precomputeAttributeDependenciesAux(doc, sel, false, false);
        break;
    case CSSSelector::SubSelector:
        precomputeAttributeDependenciesAux(doc, sel, isAncestor, isSubject);
        break;
    }
}
