selectNext0(const size_t i) const
    {
        return select0((i==0?0:rank0(i-1))+1);
    }
