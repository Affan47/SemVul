output_octets(struct ntb_quoted_printable_data *data,
              const uint8_t *octets,
              size_t length)
{
        if (data->underscore_is_space) {
                while (length > 0) {
                        if (*octets == '_')
                                *(data->out++) = ' ';
                        else
                                *(data->out++) = *octets;
                        octets++;
                        length--;
                }
        } else {
                memcpy(data->out, octets, length);
                data->out += length;
        }
}
