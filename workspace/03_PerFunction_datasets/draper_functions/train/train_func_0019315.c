icalmemory_append_string(char** buf, char** pos, size_t* buf_size,
			      const char* string)
{
    char *new_buf;
    char *new_pos;

    size_t data_length, final_length, string_length;

#ifndef ICAL_NO_INTERNAL_DEBUG
    icalerror_check_arg_rv( (buf!=0),"buf");
    icalerror_check_arg_rv( (*buf!=0),"*buf");
    icalerror_check_arg_rv( (pos!=0),"pos");
    icalerror_check_arg_rv( (*pos!=0),"*pos");
    icalerror_check_arg_rv( (buf_size!=0),"buf_size");
    icalerror_check_arg_rv( (*buf_size!=0),"*buf_size");
    icalerror_check_arg_rv( (string!=0),"string");
#endif

    string_length = strlen(string);
    data_length = (size_t)*pos - (size_t)*buf;
    final_length = data_length + string_length;

    if ( final_length >= (size_t) *buf_size) {


	*buf_size  = (*buf_size) * 2  + final_length;

	new_buf = realloc(*buf,*buf_size);

	new_pos = (void*)((size_t)new_buf + data_length);

	*pos = new_pos;
	*buf = new_buf;
    }

    strcpy(*pos, string);

    *pos += string_length;
}
