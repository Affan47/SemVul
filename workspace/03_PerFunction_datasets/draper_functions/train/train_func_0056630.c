ValueDestroy(ValueNode *node)
{
    ValueNode *p, *current;
    p = node;

    while (p) {
        current = p;
        p = p->next;
        if (current->language)
            free (current->language);
        if (current->value)
            free (current->value);
    }
}
