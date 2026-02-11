was_visited(int state_no, int symbol)
{
    struct node *p;

    for (p = visited.map[state_no]; p != NULL; p = p -> next)
    {
        if (p -> value == symbol)
            break;
    }

    return (p != NULL);
}
