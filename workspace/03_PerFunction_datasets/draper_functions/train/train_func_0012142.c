output_wave(property)
    Response_Property *property;
{
    char binary_data[EB_SIZE_PAGE];
    EB_Error_Code error_code;
    EB_Position end_position;
    ssize_t read_length;


    end_position.page = property->position.page
	+ (property->size / EB_SIZE_PAGE);
    end_position.offset = property->position.offset
	+ (property->size % EB_SIZE_PAGE);
    if (EB_SIZE_PAGE <= end_position.offset) {
	end_position.offset -= EB_SIZE_PAGE;
	end_position.page++;
    }


    error_code = eb_set_binary_wave(&property->book->book,
	&property->position, &end_position);
    if (error_code != EB_SUCCESS)
	return;

    for (;;) {
	error_code = eb_read_binary(&property->book->book, EB_SIZE_PAGE,
	    binary_data, &read_length);
	if (error_code != EB_SUCCESS || read_length == 0)
	    return;
	output_data(property, binary_data, read_length);
    }


    return;
}
