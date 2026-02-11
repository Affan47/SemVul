processDrag(int mx, int ) {
    int x = mx;

    if (fDragging == 0)
        return;

    TaskBarApp *cur = 0;
    if (x < 0) {
        cur = fFirst;
    } else if (x >= width()) {
        cur = 0;
    } else {
        int seen = 0;
        TaskBarApp *c = fFirst;
        while (c) {
            if (c == fDragging)
                seen = 1;
            if (c->getShown() && x >= c->x() && x < c->x() + c->width()) {
                if (seen)
                    cur = c->getNext();
                else
                    cur = c;
                break;
            }
            c = c->getNext();
        }
    }
    if (fDragging != 0 && cur != fDragging->getNext() && cur != fDragging) {
        remove(fDragging);
        if (cur == 0)
            insert(fDragging);
        else {
            fDragging->setNext(cur);
            fDragging->setPrev(cur->getPrev());
            if (cur->getPrev() == 0)
                fFirst = fDragging;
            else
                cur->getPrev()->setNext(fDragging);
            cur->setPrev(fDragging);
        }
        relayout();
    }
}
