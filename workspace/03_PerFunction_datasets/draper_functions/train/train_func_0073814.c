insert_objects(object *pl, object *container, object *objects[], int objects_len) {
    int i, one = 0;

    for (i = 0; i < objects_len; i++) {
        if (objects[i]->nrof > 0) {
            object_insert_in_ob(objects[i], container);
            one = 1;
        } else {
            object_free_drop_inventory(objects[i]);
        }
    }
    if (one)
        esrv_update_item(UPD_WEIGHT, pl, container);
}
