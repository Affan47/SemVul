dump_split_record(split_record record)
{
    char * string_ptr = NULL;
    char string_buf[256];

    DEBUG("dump_split_record(): Start...");
    if (record.log_action_present)
    {
        switch (record.log_action)
        {
        case LOG_BEGIN_EDIT:
            DEBUG("Log action: LOG_BEGIN_EDIT");
            break;
        case LOG_DELETE:
            DEBUG("Log action: LOG_DELETE");
            break;
        case LOG_COMMIT:
            DEBUG("Log action: LOG_COMMIT");
            break;
        case LOG_ROLLBACK:
            DEBUG("Log action: LOG_ROLLBACK");
            break;
        }
    }
    if (record.trans_guid_present)
    {
        DEBUG("Transaction GncGUID: %s", guid_to_string (&(record.trans_guid)));
    }
    if (record.split_guid_present)
    {
        DEBUG("Split GncGUID: %s", guid_to_string (&(record.split_guid)));
    }
    if (record.log_date_present)
    {
        gnc_timespec_to_iso8601_buff (record.log_date, string_buf);
        DEBUG("Log entry date: %s", string_buf);
    }
    if (record.date_entered_present)
    {
        gnc_timespec_to_iso8601_buff (record.date_entered, string_buf);
        DEBUG("Date entered: %s", string_buf);
    }
    if (record.date_posted_present)
    {
        gnc_timespec_to_iso8601_buff (record.date_posted, string_buf);
        DEBUG("Date posted: %s", string_buf);
    }
    if (record.acc_guid_present)
    {
        DEBUG("Account GncGUID: %s", guid_to_string (&(record.acc_guid)));
    }
    if (record.acc_name_present)
    {
        DEBUG("Account name: %s", record.acc_name);
    }
    if (record.trans_num_present)
    {
        DEBUG("Transaction number: %s", record.trans_num);
    }
    if (record.trans_descr_present)
    {
        DEBUG("Transaction description: %s", record.trans_descr);
    }
    if (record.trans_notes_present)
    {
        DEBUG("Transaction notes: %s", record.trans_notes);
    }
    if (record.split_memo_present)
    {
        DEBUG("Split memo: %s", record.split_memo);
    }
    if (record.split_action_present)
    {
        DEBUG("Split action: %s", record.split_action);
    }
    if (record.split_reconcile_present)
    {
        DEBUG("Split reconcile: %c", record.split_reconcile);
    }
    if (record.amount_present)
    {
        string_ptr = gnc_numeric_to_string(record.amount);
        DEBUG("Record amount: %s", string_ptr);
        g_free(string_ptr);
    }
    if (record.value_present)
    {
        string_ptr = gnc_numeric_to_string(record.value);
        DEBUG("Record value: %s", string_ptr);
        g_free(string_ptr);
    }
    if (record.date_reconciled_present)
    {
        gnc_timespec_to_iso8601_buff (record.date_reconciled, string_buf);
        DEBUG("Reconciled date: %s", string_buf);
    }
}
