pit_table_insert(PTable pt, char *record)
{
    register char *pr;
    register time_t now = time(NULL);

    if (pt->number_of_records >= pt->number_of_slots) {
        pt = table_extend(pt);
    } else {
        if (HAS_ID(pt) && pt->auto_increment >= pt->index_size) {
            table_extend_index(pt);
        }
    }

    pr = table_available_slot(pt);
    memmove(pr, record, pt->record_size);
    pt->number_of_records++;

    if (HAS_ID(pt)) {


        register char **pi = table_available_index(pt);
        *pi = pr;


        pt->auto_increment++;
        *(int *)*pi = pt->auto_increment;
    }


    if (HAS_CREATED_AT(pt) || HAS_UPDATED_AT(pt)) {
        *(time_t *)(pr + pt->record_size - sizeof(time_t)) = now;
    }
    if (HAS_CREATED_AT(pt) && HAS_UPDATED_AT(pt)) {
        *(time_t *)(pr + pt->record_size - sizeof(time_t) * 2) = now;
    }
    return pr;
}
