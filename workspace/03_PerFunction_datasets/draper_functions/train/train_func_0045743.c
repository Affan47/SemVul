osubset(us,vs)
List us, vs; {
    while (nonNull(us) && cellIsMember(hd(us),vs)) {
	us = tl(us);
    }
    return isNull(us);
}
