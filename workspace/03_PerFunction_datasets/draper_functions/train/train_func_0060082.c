get_function_name_graph(int methodId) {
    switch (methodId) {
        case GM_BLTIN_GRAPH_NUM_NODES:
            return NUM_NODES;
        case GM_BLTIN_GRAPH_NUM_EDGES:
            return NUM_EDGES;
        case GM_BLTIN_GRAPH_RAND_NODE:
            return RANDOM_NODE;
        default:
            assert(false);
            return "ERROR";
    }
}
