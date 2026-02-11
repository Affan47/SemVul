calc_time_to_wait (http_desc_t *desc)
{
    int timetowait;
    int suggested_len = ((long int)http_buffer_size * (long int)(16-desc->played_parts)) / 16;
    int useless_buffer_len = desc->pos - desc->begin;
    int useful_buffer_len = desc->len - useless_buffer_len;


    if (desc->size) {
	int rest_of_stream = desc->size - desc->buffer_pos;

	if (rest_of_stream < suggested_len)
	    suggested_len = rest_of_stream;
    };


    if (useful_buffer_len > suggested_len)
	return (int)MAX_WAIT_TIME;


    timetowait = (int)((float)useful_buffer_len / (float)suggested_len * MAX_WAIT_TIME);

    return timetowait;
}
