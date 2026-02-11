volgen_graph_set_iam_shd (volgen_graph_t *graph)
{
        xlator_t        *trav;
        int             ret = 0;

        for (trav = first_of (graph); trav; trav = trav->next) {
                if (strcmp (trav->type, "cluster/replicate") != 0)
                        continue;

                ret = xlator_set_option (trav, "iam-self-heal-daemon", "yes");
                if (ret)
                        break;
        }
        return ret;
}
