ompi_coll_tuned_mk_msg_rules (int n_msg_rules, int alg_rule_id, int com_rule_id, int mpi_comsize)
{
    int i;
    ompi_coll_msg_rule_t *msg_rules;

    msg_rules = (ompi_coll_msg_rule_t *) calloc (n_msg_rules, sizeof (ompi_coll_msg_rule_t));
    if (!msg_rules) return (msg_rules);

    for( i = 0; i < n_msg_rules; i++ ) {
        msg_rules[i].mpi_comsize = mpi_comsize;
        msg_rules[i].alg_rule_id = alg_rule_id;
        msg_rules[i].com_rule_id = com_rule_id;
        msg_rules[i].msg_rule_id = i;
        msg_rules[i].msg_size = 0;
        msg_rules[i].result_alg = 0;
        msg_rules[i].result_topo_faninout = 0;
        msg_rules[i].result_segsize = 0;
        msg_rules[i].result_max_requests = 0;
    }
    return (msg_rules);
}
