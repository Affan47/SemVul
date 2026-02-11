removeChild ( NodeImpl *oldChild, int &exceptioncode )
{
    exceptioncode = 0;


    if (isReadOnly()) {
        exceptioncode = DOMException::NO_MODIFICATION_ALLOWED_ERR;
        return;
    }


    if (!oldChild || oldChild->parentNode() != this) {
        exceptioncode = DOMException::NOT_FOUND_ERR;
        return;
    }

    dispatchChildRemovalEvents(oldChild,exceptioncode);
    if (exceptioncode)
        return;

    SharedPtr<NodeImpl> memManage(oldChild);


    if (oldChild->attached())
        oldChild->detach();


    NodeImpl *prev, *next;
    prev = oldChild->previousSibling();
    next = oldChild->nextSibling();

    if(next) next->setPreviousSibling(prev);
    if(prev) prev->setNextSibling(next);
    if(_first == oldChild) _first = next;
    if(_last == oldChild) _last = prev;

    oldChild->setPreviousSibling(0);
    oldChild->setNextSibling(0);
    oldChild->setParent(0);

    structureChanged();


    dispatchSubtreeModifiedEvent();

    NodeImpl *p = this;
    while (p->parentNode())
	p = p->parentNode();
    if (p->nodeType() == Node::DOCUMENT_NODE) {
	for (NodeImpl *c = oldChild; c; c = c->traverseNextNode(oldChild))
	    c->removedFromDocument();
    }
}
