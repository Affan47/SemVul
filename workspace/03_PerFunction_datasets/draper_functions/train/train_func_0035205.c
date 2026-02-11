testStPinchThread_pinchP(CuTest *testCase, int64_t segmentNumber, int64_t start, int64_t lengths[],
        int64_t blockDegrees[], stPinchThread *thread) {
    stPinchSegment *segment = stPinchThread_getFirst(thread);
    int64_t i = start;
    for (int64_t j = 0; j < segmentNumber; j++) {
        CuAssertTrue(testCase, segment != NULL);
        CuAssertIntEquals(testCase, stPinchThread_getName(thread), stPinchSegment_getName(segment));
        CuAssertIntEquals(testCase, i, stPinchSegment_getStart(segment));
        CuAssertIntEquals(testCase, lengths[j], stPinchSegment_getLength(segment));

        if (blockDegrees[j] == 1) {
            CuAssertPtrEquals(testCase, NULL, stPinchSegment_getBlock(segment));
        } else {
            stPinchBlock *block = stPinchSegment_getBlock(segment);
            CuAssertTrue(testCase, block != NULL);
            CuAssertIntEquals(testCase, blockDegrees[j], stPinchBlock_getDegree(block));
        }

        i += stPinchSegment_getLength(segment);
        if (j + 1 == segmentNumber) {
            CuAssertTrue(testCase, stPinchSegment_get3Prime(segment) == NULL);
        } else {
            stPinchSegment *segment2 = stPinchSegment_get3Prime(segment);
            CuAssertTrue(testCase, segment2 != NULL);
            CuAssertPtrEquals(testCase, segment, stPinchSegment_get5Prime(segment2));
            segment = segment2;
        }
    }
}
