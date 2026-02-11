ompi_coll_tuned_free_coms_in_alg_rule (ompi_coll_alg_rule_t* alg_p)
{
    int rc=0;
    int i;

    ompi_coll_com_rule_t* com_p;

    if (!alg_p) {
        OPAL_OUTPUT((ompi_coll_tuned_stream,"attempt to free NULL alg_rule ptr\n"));
        return (-1);
    }

    if (alg_p->n_com_sizes) {
        com_p = alg_p->com_rules;

        if (!com_p) {
            OPAL_OUTPUT((ompi_coll_tuned_stream,"attempt to free NULL com_rules when com count was %d\n", alg_p->n_com_sizes));
        } else {

            for( i = 0; i < alg_p->n_com_sizes; i++ ) {
                com_p = &(alg_p->com_rules[i]);
                ompi_coll_tuned_free_msg_rules_in_com_rule (com_p);
            }

            free (alg_p->com_rules);
            alg_p->com_rules = (ompi_coll_com_rule_t*) NULL;
        }

    }

    return (rc);
}
