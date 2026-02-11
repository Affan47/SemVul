gm_type_error(int errno, ast_id* id1, ast_id* id2) {
    gm_print_error_header();
    if (curr_file != NULL) printf("%s:", curr_file);
    printf("%d: %d: error: ", id1->get_line(), id1->get_col());
    switch (errno) {
        case GM_ERROR_NONGRAPH_TARGET:
            printf("%s is not a graph type object\n", id1->get_orgname());
            break;
        case GM_ERROR_NONSET_TARGET:
            printf("%s is not a collection type object\n", id1->get_orgname());
            break;
        case GM_ERROR_NONNODE_TARGET:
            printf("%s is not a node-compatible type object\n", id1->get_orgname());
            break;
        case GM_ERROR_TARGET_GRAPH_MISMATCH:
            printf("%s and %s are not bound to the same graph\n", id1->get_orgname(), id2->get_orgname());
            break;
        case GM_ERROR_UNDEFINED_FIELD_GRAPH:
            printf("Property %s is not defined for graph %s.\n", id1->get_orgname(), id2->get_orgname());
            break;
        case GM_ERROR_DUPLICATE:
            printf("%s is defined more than one time. (First defined in line %d : %d)\n", id1->get_orgname(), id2->get_line(), id2->get_col());
            break;
        case GM_ERROR_TARGET_MISMATCH:
            printf("Target Graphs mismatches %s, %s.\n", id1->get_orgname(), id2->get_orgname());
            break;

        case GM_ERROR_DEFAULT_GRAPH_AMBIGUOUS:
            printf("More than one graph present. Explicit binding of nodes, edges, properties and collections is required!\n");
            break;

        case GM_ERROR_UNKNOWN:
        default:
            printf("Unknown error 3\n");
            break;
    }
}
