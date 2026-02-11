common_update_score(resource_t * rsc, const char *id, int score)
{
    node_t *node = NULL;

    node = pe_hash_table_lookup(rsc->allowed_nodes, id);
    if (node != NULL) {
        pe_rsc_trace(rsc, "Updating score for %s on %s: %d + %d", rsc->id, id, node->weight, score);
        node->weight = merge_weights(node->weight, score);
    }

    if (rsc->children) {
        GListPtr gIter = rsc->children;

        for (; gIter != NULL; gIter = gIter->next) {
            resource_t *child_rsc = (resource_t *) gIter->data;

            common_update_score(child_rsc, id, score);
        }
    }
}
