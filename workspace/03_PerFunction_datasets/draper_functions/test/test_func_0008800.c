PyThread_delete_key(int key)
{
    struct key *p, **q;

    PyThread_acquire_lock(keymutex, 1);
    q = &keyhead;
    while ((p = *q) != NULL) {
        if (p->key == key) {
            *q = p->next;
            free((void *)p);

        }
        else
            q = &p->next;
    }
    PyThread_release_lock(keymutex);
}
