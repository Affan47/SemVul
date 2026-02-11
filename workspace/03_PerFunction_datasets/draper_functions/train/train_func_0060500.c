http_parse_response(struct http_ctrl_t *http_ctrl,
			struct http_header_t *http_hdr)
{
    char *content_length = NULL;

    content_length = http_get_field(http_hdr, "Content-Length");
    if(content_length) {
	http_ctrl->content_length = atoi(content_length);
    }
    else {
	http_ctrl->content_length = 0;
    }

    return 1;
}
