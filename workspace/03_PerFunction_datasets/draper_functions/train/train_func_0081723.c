generateLists() {

    if(!items.empty()) {
        if(!listid) listid = glGenLists(1);

        glNewList(listid, GL_COMPILE);

        for(std::list<QuadItem*>::iterator it = items.begin(); it != items.end(); it++) {
            QuadItem* oi = (*it);
            oi->drawQuadItem();
        }

        glEndList();
        return;
    }

    if(!children.empty()) {
        for(int i=0;i<4;i++) {
            QuadNode* c = children[i];
            if(!c->empty()) {
                c->generateLists();
            }
        }
    }
}
