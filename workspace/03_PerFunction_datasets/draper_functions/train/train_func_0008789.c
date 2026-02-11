port_add(int port)
{
    Octstr *key;
    struct port *p;

    key = port_key(port);
    mutex_lock(port_mutex);
    if ((p = dict_get(port_collection, key)) == NULL) {
        p = gw_malloc(sizeof(*p));
        p->clients_with_requests = gwlist_create();
        gwlist_add_producer(p->clients_with_requests);
        p->active_consumers = counter_create();
        dict_put(port_collection, key, p);
    } else {
        warning(0, "HTTP: port_add called for existing port (%d)", port);
    }
    mutex_unlock(port_mutex);
    octstr_destroy(key);
}
