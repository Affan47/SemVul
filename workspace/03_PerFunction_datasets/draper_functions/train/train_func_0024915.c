isInRange(long p1, long p2) const {
        arb_assert(p1 <= p2);
        return p1 <= pos1 && pos2 <= p2;
    }
