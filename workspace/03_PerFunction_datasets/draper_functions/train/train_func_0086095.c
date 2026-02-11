tree_find(KeyBindingTree *search, gboolean *conflict)
{
    KeyBindingTree *a, *b;

    *conflict = FALSE;

    a = keyboard_firstnode;
    b = search;
    while (a && b) {


        if (!(a->state == b->state && a->key == b->key && b->key != 0)) {
            a = a->next_sibling;
        } else {
            if ((a->first_child == NULL) == (b->first_child == NULL)) {
                if (a->first_child == NULL) {

                    return a;
                }
            } else {
                *conflict = TRUE;
                return NULL;
            }
            b = b->first_child;
            a = a->first_child;
        }
    }
    return NULL;
}
