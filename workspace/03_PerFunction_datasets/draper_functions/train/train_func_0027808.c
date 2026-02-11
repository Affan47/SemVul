globus_l_rvf_records_destroy(globus_list_t *records)
{
    globus_list_t * l = records;
    while (!globus_list_empty(l))
    {
        globus_rvf_record_t *           record;

        record = globus_list_remove(&l, l);

        globus_l_rvf_validation_record_destroy(record);
    }
}
