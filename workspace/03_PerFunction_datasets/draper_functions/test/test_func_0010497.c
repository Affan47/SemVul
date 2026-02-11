stPinchThreadSet_getRandomPinch(stPinchThreadSet *threadSet) {
    stPinchThread *thread1, *thread2;
    int64_t start1, start2;
    bool strand1, strand2;
    getRandomPosition(threadSet, &thread1, &start1, &strand1);
    getRandomPosition(threadSet, &thread2, &start2, &strand2);
    int64_t i = stPinchThread_getStart(thread1) + stPinchThread_getLength(thread1) - start1;
    int64_t j = stPinchThread_getStart(thread2) + stPinchThread_getLength(thread2) - start2;
    assert(i >= 0 && j >= 0);
    i = i > j ? j : i;
    int64_t length = i == 0 ? 0 : st_randomInt(0, i);
    stPinch pinch = stPinch_constructStatic(stPinchThread_getName(thread1), stPinchThread_getName(thread2), start1, start2, length, strand1 == strand2);
    return pinch;
}
