stPinchInterval_compareFunction(const stPinchInterval *interval1, const stPinchInterval *interval2) {
    int i = cmp64s(interval1->name, interval2->name);
    if (i != 0) {
        return i;
    }
    i = cmp64s(interval1->start, interval2->start);
    if (i != 0) {
        return i;
    }
    return cmp64s(interval2->length, interval1->length);
}
