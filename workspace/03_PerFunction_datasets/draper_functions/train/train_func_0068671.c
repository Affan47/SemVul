allocate_action_element(void)
{
    struct action_element *p;

    p = action_element_pool;
    if (p != NULL)
        action_element_pool = p -> next;
    else
    {
        p = (struct action_element *)
            talloc(sizeof(struct action_element));
        if (p == (struct action_element *) NULL)
            nospace(__FILE__, __LINE__);
    }

    return p;
}
