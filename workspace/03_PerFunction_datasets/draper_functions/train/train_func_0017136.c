destructor(opal_hotel_t *h)
{
    int i;


    for (i = 0; i < h->num_rooms; ++i) {
        if (NULL != h->rooms[i].occupant) {
            opal_event_del(&(h->rooms[i].eviction_timer_event));
        }
    }

    if (NULL != h->rooms) {
        free(h->rooms);
    }
    if (NULL != h->eviction_args) {
        free(h->eviction_args);
    }
    if (NULL != h->unoccupied_rooms) {
        free(h->unoccupied_rooms);
    }
}
