opal_list_splice(opal_list_t *thislist, opal_list_item_t *pos,
                 opal_list_t *xlist, opal_list_item_t *first,
                 opal_list_item_t *last)
{
    size_t change = 0;
    opal_list_item_t *tmp;

    if (first != last) {


        for (tmp = first ; tmp != last ; tmp = opal_list_get_next(tmp)) {
            change++;
        }

        opal_list_transfer(pos, first, last);


        thislist->opal_list_length += change;
        xlist->opal_list_length -= change;
    }
}
