icaldurationtype_as_ical_string(struct icaldurationtype d)
{

    char *buf, *output_line;
    size_t buf_size = 256;
    char* buf_ptr = 0;
    int seconds;

    buf = (char*)icalmemory_new_buffer(buf_size);
    buf_ptr = buf;


    seconds = icaldurationtype_as_int(d);

    if(seconds !=0){

	if(d.is_neg == 1){
	    icalmemory_append_char(&buf, &buf_ptr, &buf_size, '-');
	}

	icalmemory_append_char(&buf, &buf_ptr, &buf_size, 'P');

	if (d.weeks != 0 ) {
	    append_duration_segment(&buf, &buf_ptr, &buf_size, "W", d.weeks);
	}

	if (d.days != 0 ) {
	    append_duration_segment(&buf, &buf_ptr, &buf_size, "D", d.days);
	}

	if (d.hours != 0 || d.minutes != 0 || d.seconds != 0) {

	    icalmemory_append_string(&buf, &buf_ptr, &buf_size, "T");

	    if (d.hours != 0 ) {
		append_duration_segment(&buf, &buf_ptr, &buf_size, "H", d.hours);
	    }
	    if (d.minutes != 0 ) {
		append_duration_segment(&buf, &buf_ptr, &buf_size, "M",
					d.minutes);
	    }
	    if (d.seconds != 0 ) {
		append_duration_segment(&buf, &buf_ptr, &buf_size, "S",
					d.seconds);
	    }

	}
    } else {
	icalmemory_append_string(&buf, &buf_ptr, &buf_size, "PTS0");
    }

    output_line = icalmemory_tmp_copy(buf);
    icalmemory_free_buffer(buf);

    return output_line;

}
