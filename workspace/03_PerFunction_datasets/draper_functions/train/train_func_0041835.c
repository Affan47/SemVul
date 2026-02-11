data_from_static_ptr (void *value)
{


        data_t *data = get_new_data ();

        if (!data) {
                return NULL;
        }

        data->is_static = 1;
        data->data = value;

        return data;
}
