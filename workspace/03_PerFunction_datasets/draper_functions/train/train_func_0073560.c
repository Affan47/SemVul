data_from_dynstr (char *value)
{
        if (!value) {
                gf_log_callingfn ("dict", GF_LOG_WARNING, "value is NULL");
                return NULL;
        }

        data_t *data = get_new_data ();

        data->len = strlen (value) + 1;
        data->data = value;

        return data;
}
