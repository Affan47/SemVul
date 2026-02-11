compareCEs(uint32_t source0, uint32_t source1, uint32_t target0, uint32_t target1) {
    uint32_t s1 = source0, s2, t1 = target0, t2;
    if(isContinuation(source1)) {
        s2 = source1;
    } else {
        s2 = 0;
    }
    if(isContinuation(target1)) {
        t2 = target1;
    } else {
        t2 = 0;
    }

    uint32_t s = 0, t = 0;
    if(s1 == t1 && s2 == t2) {
        return 0;
    }
    s = (s1 & 0xFFFF0000)|((s2 & 0xFFFF0000)>>16);
    t = (t1 & 0xFFFF0000)|((t2 & 0xFFFF0000)>>16);
    if(s < t) {
        return -1;
    } else if(s > t) {
        return 1;
    } else {
        s = (s1 & 0x0000FF00) | (s2 & 0x0000FF00)>>8;
        t = (t1 & 0x0000FF00) | (t2 & 0x0000FF00)>>8;
        if(s < t) {
            return -1;
        } else if(s > t) {
            return 1;
        } else {
            s = (s1 & 0x000000FF)<<8 | (s2 & 0x000000FF);
            t = (t1 & 0x000000FF)<<8 | (t2 & 0x000000FF);
            if(s < t) {
                return -1;
            } else {
                return 1;
            }
        }
    }
}
