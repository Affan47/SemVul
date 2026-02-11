clear_pattern_list (stripe_private_t *priv)
{
        struct stripe_options *prev = NULL;
        struct stripe_options *trav = NULL;
        int                    ret = -1;

        GF_VALIDATE_OR_GOTO ("stripe", priv, out);

        trav = priv->pattern;
        priv->pattern = NULL;
        while (trav) {
                prev = trav;
                trav = trav->next;
                GF_FREE (prev);
        }

        ret = 0;
 out:
        return ret;


}
