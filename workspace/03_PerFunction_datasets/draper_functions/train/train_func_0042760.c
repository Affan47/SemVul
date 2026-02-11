select(uint symbol, size_t pos, uint l, wt_coder * c) const
    {
        bool is_set = c->is_set(symbol, l);
        size_t ret = 0;
        if(!is_set) {
            if(left_child==NULL)
                return (size_t)(-1);
            size_t new_pos = left_child->select(symbol, pos, l+1,c);
            if(new_pos+1==0) return (uint)(-1);
            ret = bitmap->select0(new_pos)+1;
        }
        else {
            if(right_child==NULL)
                return (size_t)(-1);
            size_t new_pos = right_child->select(symbol, pos, l+1,c);
            if(new_pos+1==0) return (uint)(-1);
            ret = bitmap->select1(new_pos)+1;
        }
        if(ret==0) return (size_t)-1;
        return ret;
    }
