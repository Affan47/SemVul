test_3EdgeFunction(CuTest *testCase) {


    for(int64_t test=0; test<100; test++) {


        int64_t vertexNumber = st_randomInt(0, 100);
        int64_t edgeNumber = vertexNumber > 0 ? st_randomInt(0, vertexNumber * vertexNumber) : 0;
        stList *vertices = getRandomGraph(vertexNumber, edgeNumber);


        stList *threeEdgeConnectedComponents = computeThreeEdgeConnectedComponents(vertices);


        stSortedSet *seen = stSortedSet_construct3((int (*)(const void *, const void *))stIntTuple_cmpFn, NULL);
        stListIterator *it = stList_getIterator(threeEdgeConnectedComponents);
        stList *threeEdgeConnectedComponent;
        while((threeEdgeConnectedComponent = stList_getNext(it)) != NULL) {
            stListIterator *it2 = stList_getIterator(threeEdgeConnectedComponent);
            stIntTuple *vertex;
            while((vertex = stList_getNext(it2)) != NULL) {
                CuAssertTrue(testCase, stSortedSet_search(seen, vertex) == NULL);
                stSortedSet_insert(seen, vertex);


            }
            stList_destructIterator(it2);
        }
        stList_destructIterator(it);
        CuAssertTrue(testCase, stList_length(vertices) == stSortedSet_size(seen));


        stList_destruct(vertices);
        stSortedSet_destruct(seen);
    }
}
