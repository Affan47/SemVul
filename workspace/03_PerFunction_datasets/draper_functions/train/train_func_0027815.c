stPinchThread_filterPinchNegativeStrand(stPinchThread *thread1, stPinchThread *thread2, int64_t start1, int64_t start2,
        int64_t length, bool(*filterFn)(stPinchSegment *, stPinchSegment *)) {
    stPinchSegment *segment1 = stPinchThread_getSegment(thread1, start1);
    stPinchSegment *segment2 = stPinchThread_getSegment(thread2, start2 + length - 1);
    int64_t offset = 0;
    while  (offset < length) {
        assert(segment1 != NULL);
        assert(segment2 != NULL);
        if (filterFn(segment1, segment2)) {
            stPinchThread_filterPinchNegativeStrandP(&segment1, &segment2, start1, start2 + length, &offset);
        } else {
            int64_t start = offset;
            stPinchSegment *s1 = segment1;
            stPinchThread_filterPinchNegativeStrandP(&segment1, &segment2, start1, start2 + length, &offset);
            assert(offset - start > 0);
            if (offset > length) {
                stPinchThread_pinchNegative2(s1, thread2, start1 + start, start2, length - start);
                break;
            }
            else {
                stPinchThread_pinchNegative2(s1, thread2, start1 + start, start2 + length - offset, offset - start);
            }
            segment1 = stPinchThread_getSegment(thread1, start1 + offset);
            segment2 = stPinchThread_getSegment(thread2, start2 + length - 1 - offset);
        }
    }
}
