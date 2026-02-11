selectPrev1(const size_t start) const
    {


        uint i = start >> 5;
        int offset = (start % W);
        uint aux2 = data[i] & (-1u >> (31-offset));

        if (aux2 > 0) {
            if ((aux2&0xFF000000) > 0) return i*W+23+prev_tab[(aux2>>24)&0xFF];
            else if ((aux2&0xFF0000) > 0) return i*W+15+prev_tab[(aux2>>16)&0xFF];
            else if ((aux2&0xFF00) > 0) return i*W+7+prev_tab[(aux2>>8)&0xFF];
            else  return i*W+prev_tab[aux2&0xFF]-1;
        }
        for (uint k=i-1;;k--) {
            aux2=data[k];
            if (aux2 > 0) {
                if ((aux2&0xFF000000) > 0) return k*W+23+prev_tab[(aux2>>24)&0xFF];
                else if ((aux2&0xFF0000) > 0) return k*W+15+prev_tab[(aux2>>16)&0xFF];
                else if ((aux2&0xFF00) > 0) return k*W+7+prev_tab[(aux2>>8)&0xFF];
                else  return k*W+prev_tab[aux2&0xFF]-1;
            }
        }
        return 0;
    }
