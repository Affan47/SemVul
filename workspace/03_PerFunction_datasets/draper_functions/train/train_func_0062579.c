del_session(struct session **sp, int sid)
{

    struct session *tmp;

    if (*sp == NULL) return NULL;
    if ((*sp)->sid == sid) {
        tmp = *sp;
        *sp = tmp->next;
        return tmp;
    }
    tmp = (*sp)->next;
    while (tmp != NULL) {
        if (tmp->sid == sid) {
            (*sp)->next = tmp->next;
            return tmp;
        }
        sp = &((*sp)->next);
        tmp = tmp->next;
    }
    return NULL;
}
