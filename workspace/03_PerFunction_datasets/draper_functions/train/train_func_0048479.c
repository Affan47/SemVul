is_data_equal (data_t *one,
               data_t *two)
{

        if (!one || !two || !one->data || !two->data)
                return 1;

        if (one == two)
                return 1;

        if (one->len != two->len)
                return 0;

        if (one->data == two->data)
                return 1;

        if (memcmp (one->data, two->data, one->len) == 0)
                return 1;

        return 0;
}
