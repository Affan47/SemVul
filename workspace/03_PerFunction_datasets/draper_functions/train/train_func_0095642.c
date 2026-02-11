object_split(object *orig_ob, uint32 nr, char *err, size_t size) {
    object *newob;

    if (MAX(1, orig_ob->nrof) < nr) {

        if (err)
            snprintf(err, size, "There are only %u %ss.", orig_ob->nrof ? orig_ob->nrof : 1, orig_ob->name);
        else
            LOG(llevDebug, "There are only %u %ss.\n", orig_ob->nrof ? orig_ob->nrof : 1, orig_ob->name);
        return NULL;
    }
    newob = object_create_clone(orig_ob);
    if (orig_ob->nrof == 0) {
        if (!QUERY_FLAG(orig_ob, FLAG_REMOVED)) {
            object_remove(orig_ob);
        }
        object_free2(orig_ob, FREE_OBJ_FREE_INVENTORY);
    } else {
        newob->nrof = nr;
        object_decrease_nrof(orig_ob, nr);
    }

    return newob;
}
