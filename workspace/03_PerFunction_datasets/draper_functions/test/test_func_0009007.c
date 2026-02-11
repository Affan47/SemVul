vis_link_visual( visual_t *list,visual_t *new )
{
    visual_t *ptr = list;

    if ( list )
    {
        while( ptr->Next != NULL ) ptr = ptr->Next;
        ptr->Next = new;
    } else list = new;

    return list;
}
