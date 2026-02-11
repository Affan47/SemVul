is_worn_by_type(struct obj *otmp)
{
    return ((!!(otmp->owornmask &
                (W_ARMOR | W_RING | W_AMUL | W_TOOL | W_WEP | W_SWAPWEP | W_QUIVER)))
            && (index(valid_menu_classes, otmp->oclass) != (char *)0));
}
