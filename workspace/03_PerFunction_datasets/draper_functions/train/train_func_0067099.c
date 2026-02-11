stPinchThread_joinTrivialBoundaries(stPinchThread *thread) {
    stPinchSegment *segment = stPinchThread_getFirst(thread);
    do {
        if (stPinchSegment_getBlock(segment) == NULL) {
            while (1) {
                stPinchSegment *nSegment = stPinchSegment_get3Prime(segment);
                if (nSegment != NULL) {
                    stPinchBlock *nBlock = stPinchSegment_getBlock(nSegment);
                    if (nBlock == NULL) {

                        segment->nSegment = nSegment->nSegment;
                        assert(nSegment->nSegment != NULL);
                        nSegment->nSegment->pSegment = segment;
                        stSortedSet_remove(thread->segments, nSegment);
                        stPinchSegment_destruct(nSegment);
                        continue;
                    }
                }
                break;
            }
        }
    } while ((segment = stPinchSegment_get3Prime(segment)) != NULL);
}
