stCactusGraph_collapseToCactus(stCactusGraph *graph, void *(*mergeNodeObjects)(void *, void *), stCactusNode *startNode) {

    stHash *nodesToPositions = stHash_construct();
    stHash *positionsToNodes = stHash_construct3((uint64_t(*)(const void *)) stIntTuple_hashKey,
            (int(*)(const void *, const void *)) stIntTuple_equalsFn, (void(*)(void *)) stIntTuple_destruct, NULL);
    stList *adjacencyList = stList_construct3(0, (void(*)(void *)) stList_destruct);


    stCactusGraphNodeIt *nodeIt = stCactusGraphNodeIterator_construct(graph);
    stCactusNode *node;
    int64_t nodeIdCounter = 0;
    while ((node = stCactusGraphNodeIterator_getNext(nodeIt)) != NULL) {
        stIntTuple *nodeId = stIntTuple_construct1( nodeIdCounter++);
        stHash_insert(nodesToPositions, node, nodeId);
        stHash_insert(positionsToNodes, nodeId, node);
    }
    stCactusGraphNodeIterator_destruct(nodeIt);
    nodeIt = stCactusGraphNodeIterator_construct(graph);
    while ((node = stCactusGraphNodeIterator_getNext(nodeIt)) != NULL) {
        stList *edges = stList_construct();
        stList_append(adjacencyList, edges);
        stCactusNodeEdgeEndIt edgeEndIt = stCactusNode_getEdgeEndIt(node);
        stCactusEdgeEnd *edgeEnd;
        while ((edgeEnd = stCactusNodeEdgeEndIt_getNext(&edgeEndIt)) != NULL) {
            stCactusNode *otherNode = stCactusEdgeEnd_getOtherNode(edgeEnd);
            stIntTuple *otherNodeId = stHash_search(nodesToPositions, otherNode);
            assert(otherNodeId != NULL);
            stList_append(edges, otherNodeId);
        }
    }
    stCactusGraphNodeIterator_destruct(nodeIt);

    stList *_3EdgeConnectedComponents = computeThreeEdgeConnectedComponents(adjacencyList);
    for (int64_t i = 0; i < stList_length(_3EdgeConnectedComponents); i++) {
        stList *_3EdgeConnectedComponent = stList_get(_3EdgeConnectedComponents, i);
        stCactusNode *node = stHash_search(positionsToNodes, stList_get(_3EdgeConnectedComponent, 0));
        assert(node != NULL);
        for (int64_t j = 1; j < stList_length(_3EdgeConnectedComponent); j++) {
            stCactusNode *otherNode = stHash_search(positionsToNodes, stList_get(_3EdgeConnectedComponent, j));
            assert(otherNode != NULL);
            assert(node != otherNode);
            if (otherNode == startNode) {
                otherNode = node;
                node = startNode;
            }
            stCactusNode_mergeNodes(graph, node, otherNode, mergeNodeObjects);
        }
    }

    stList_destruct(adjacencyList);
    stList_destruct(_3EdgeConnectedComponents);
    stHash_destruct(nodesToPositions);
    stHash_destruct(positionsToNodes);


    stCactusGraph_markCycles(graph, startNode);
}
