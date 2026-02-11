zap_actions(struct session *ses)
{
    struct listnode *l,*ln,*ol;

    ln =(ol=ses->actions)->next;
    while (ln)
        if (strcmp(ln->left,K_ACTION_MAGIC))
            ln=(ol=ln)->next;
        else
        {
            l=ln;
            ol->next=ln=ln->next;
            SFREE(l->left);
            SFREE(l->right);
            SFREE(l->pr);
            LFREE(l);
        }
    ln =(ol=ses->prompts)->next;
    while (ln)
        if (strcmp(ln->left,K_ACTION_MAGIC))
            ln=(ol=ln)->next;
        else
        {
            l=ln;
            ol->next=ln=ln->next;
            SFREE(l->left);
            SFREE(l->right);
            SFREE(l->pr);
            LFREE(l);
        }
    deletedActions=0;
}
