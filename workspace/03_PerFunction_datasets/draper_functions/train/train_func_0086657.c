opal_list_construct(opal_list_t *list)
{
#if OPAL_ENABLE_DEBUG


    OBJ_CONSTRUCT( &(list->opal_list_sentinel), opal_list_item_t );
    list->opal_list_sentinel.opal_list_item_refcount  = 1;
    list->opal_list_sentinel.opal_list_item_belong_to = list;
#endif

    list->opal_list_sentinel.opal_list_next = &list->opal_list_sentinel;
    list->opal_list_sentinel.opal_list_prev = &list->opal_list_sentinel;
    list->opal_list_length = 0;
}
