xlator_tree_free (xlator_t *tree)
{
        xlator_t *trav = tree;
        xlator_t *prev = tree;

        if (!tree) {
                gf_log ("parser", GF_LOG_ERROR, "Translator tree not found");
                return -1;
        }

        while (prev) {
                trav = prev->next;
                dict_destroy (prev->options);
                GF_FREE (prev->name);
                GF_FREE (prev->type);
                GF_FREE (prev);
                prev = trav;
        }

        return 0;
}
