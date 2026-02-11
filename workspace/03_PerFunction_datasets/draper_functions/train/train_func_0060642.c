prepend(KCompTreeNode *item)
{
    m_count++;
    if (!last) {
        last = item;
        last->next = 0;
        first = item;
        return;
    }
    item->next = first;
    first = item;
}
