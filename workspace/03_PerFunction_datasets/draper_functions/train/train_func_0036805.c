FindElement(TGlue* tg, TElement*& elem) {
    register TNodeList* nl;
    TNode* node;
    TElementList* el;

    elem = nil;

    for (nl = First(); nl != End() && elem == nil; nl = nl->Next()) {
	node = nl->GetNode();
	el = node->LeftBottomElements();
	FindElement(el, tg, elem);

	if (elem == nil) {
	    el = node->RightTopElements();
	    FindElement(el, tg, elem);
	}
    }
}
