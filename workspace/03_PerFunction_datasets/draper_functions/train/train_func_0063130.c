access(size_t i) const
    {
        uint g = groupsIndex->access(i);
        if(g<=cut) return alphSortedByFreq[g];
        uint o = indexesByLength[g-cut-1]->access(groupsIndex->rank(g,i)-1);
        return alphSortedByFreq[(1<<(g-cut+bits(cut)-1))+o];
    }
