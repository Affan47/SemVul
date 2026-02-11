sync_mailbox_finduid(struct mailbox *mailbox, unsigned uid)
{
    unsigned low=1, high=mailbox->i.num_records, mid;
    struct index_record record;

    while (low <= high) {
        mid = (high - low)/2 + low;
	if (mailbox_read_index_record(mailbox, mid, &record))
	    return 0;

        if (record.uid == uid)
            return mid;
        else if (record.uid > uid)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0;
}
