stPinchSegment_compare(const stPinchSegment *segment1, const stPinchSegment *segment2) {
    if(segment1->thread->name != segment2->thread->name) {
        return segment1->thread->name > segment2->thread->name ? 1 : -1;
    }
    return stPinchSegment_compareBySequencePosition(segment1, segment2);
}
