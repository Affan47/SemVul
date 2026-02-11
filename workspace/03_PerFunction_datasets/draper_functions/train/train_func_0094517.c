copy_temp_table(Temp_table *tpt)
{
    Temp_table *ntpt = NULL;

    if (tpt != NULL) {
        ntpt = alloc_temp_table();
	ntpt->entry = tpt->entry;
	ntpt->type = tpt->type;
	ntpt->size = tpt->size;
	ntpt->length_dummy = ntpt->length_dummy;
        ntpt->next = NULL;

        ntpt->type_entry = tpt->type_entry;
    }

    return ntpt;
}
