mmsh_streaming_read(struct stream_t *stream,
			uint8_t *buffer, size_t buffer_size)
{
    struct stream_ctrl_t *stream_ctrl = stream->stream_ctrl;
    size_t pos = 0;
    int network_read = 0;

    if(buffer_size == 0) {
	display(MSDL_ERR,"buffer_size must be bigger than 0\n");
	return -1;
    }

    if(stream_ctrl->write_data_len) {

	if(buffer_size <= stream_ctrl->write_data_len) {


	    memcpy(buffer,stream_ctrl->write_buffer + stream_ctrl->write_pos,
		   buffer_size);
	    stream_ctrl->write_data_len -= buffer_size;
	    stream_ctrl->write_pos += buffer_size;
	    return buffer_size;
	}
	else {


	    memcpy(buffer,stream_ctrl->write_buffer + stream_ctrl->write_pos,
		   stream_ctrl->write_data_len);
	    pos = stream_ctrl->write_data_len;

	    stream_ctrl->write_data_len = 0;
	    stream_ctrl->write_pos = 0;
	}
    }

    stream_ctrl->write_data_len = 0;
    stream_ctrl->write_pos = 0;


    if(stream_ctrl->status != STREAMING_FINISHED) {
	network_read = mmsh_get_media_packet(stream, buffer + pos, buffer_size - pos);
    }

    if(stream_ctrl->status == STREAMING_RESUME_BUFFERING && network_read >= 0) {
	return 0;
    }
    else if(network_read >= 0) {
	return (network_read + pos);
    }
    else {
        return -1;
    }
}
