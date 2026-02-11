select(uint c, size_t i) const
    {
        uint pos = revPermFreq[c];
        if(pos<=cut) {
            return groupsIndex->select(pos,i);
        }
        uint g = group(pos,cut);
        uint o = offset(pos,cut,g);
        return groupsIndex->select(g,indexesByLength[g-cut-1]->select(o,i)+1);
    }
