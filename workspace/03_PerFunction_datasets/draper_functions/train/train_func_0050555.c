crm_update_peer_expected(const char *source, crm_node_t * node, const char *expected)
{
    char *last = NULL;
    gboolean changed = FALSE;

    CRM_CHECK(node != NULL, crm_err("%s: Could not set 'expected' to %s", source, expected);
              return);

    last = node->expected;
    if (expected != NULL && safe_str_neq(node->expected, expected)) {
        node->expected = strdup(expected);
        changed = TRUE;
    }

    if (changed) {
        crm_info("%s: Node %s[%u] - expected state is now %s", source, node->uname, node->id,
                 expected);
        free(last);
    } else {
        crm_trace("%s: Node %s[%u] - expected state is unchanged (%s)", source, node->uname,
                  node->id, expected);
    }
}
