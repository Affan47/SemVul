getChildIndex(const vec2 & pos) const{

    if(children.empty()) return -1;

    for(int i=0;i<4;i++) {
        if(children[i]->bounds.contains(pos)) {
            return i;
        }
    }

    return -1;
}
