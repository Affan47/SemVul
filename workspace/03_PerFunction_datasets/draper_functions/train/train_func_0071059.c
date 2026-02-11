delete_list(struct process *p)
{
    while (p)
    {
        struct process * curr = p;

        if (p->name)
            gktop_free(p->name);
        p = p->next;

        gktop_free(curr);
    }
}
