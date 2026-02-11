find_po(PANEL *pan)
{
    list_of_panels *temp;
    for (temp = lop; temp->po->pan != pan; temp = temp->next)
        if (temp->next == NULL) return NULL;
    return temp->po;
}
