bitzero (register uint *e, register uint p,
    register uint len) {

        e += p/W; p %= W;
        if (p+len >= W) {
            *e &= ~((1<<p)-1);
            len -= p;
            e++; p = 0;
        }
        while (len >= W) {
            *e++ = 0;
            len -= W;
        }
        if (len > 0)
            *e &= ~(((1<<len)-1)<<p);
    }
