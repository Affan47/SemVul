data_to_int8 (data_t *data)
{
	int32_t value = 0;

        if (!data) {
                gf_log_callingfn ("dict", GF_LOG_WARNING, "data is NULL");
                return -1;
        }

        char *str = alloca (data->len + 1);
        if (!str)
                return -1;

        memcpy (str, data->data, data->len);
        str[data->len] = '\0';

	errno = 0;
	value = strtol (str, NULL, 0);

	if ((SCHAR_MAX > value) || (SCHAR_MIN < value)) {
		errno = ERANGE;
                gf_log_callingfn ("dict", GF_LOG_WARNING,
				  "Error in data conversion: "
				  "detected overflow");
                return -1;
	}

        return (int8_t)value;
}
