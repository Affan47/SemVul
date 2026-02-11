data_to_int64 (data_t *data)
{
        if (!data) {
                gf_log_callingfn ("dict", GF_LOG_WARNING, "data is NULL");
                return -1;
        }

        char *str = alloca (data->len + 1);
        if (!str)
                return -1;

        memcpy (str, data->data, data->len);
        str[data->len] = '\0';
        return (int64_t) strtoull (str, NULL, 0);
}
