lower_bound(int v) {
        int i;
        if (this->nelems == 0) {
            i = this->impl.size();
        } else {
#if 0
            for (i = 0; i < this->impl.size(); ++i) {
                if (this->present[i] && !(this->impl[i] < v)) {
                    break;
                }
            }
#else
            int l = 0, r = this->nchunks;
            int m;
            while (l != r) {
                m = l + (r-l)/2;
                int sz;
                int left = left_interval_boundary(m * chunk_size, chunk_size);
                int pos = lb_in_chunk(left, v);


                if (pos == left + chunk_size) {

                    l = m + 1;
                } else {
                    r = m;
                }
            }
            i = l * chunk_size;
#endif
        }
        dprintf("lower_bound(%d) == %d\n", v, i);
        return i;
    }
