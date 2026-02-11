ne_add_depth_header(ne_request *req, int depth)
{
    const char *value;
    switch(depth) {
    case NE_DEPTH_ZERO:
	value = "0";
	break;
    case NE_DEPTH_ONE:
	value = "1";
	break;
    default:
	value = "infinity";
	break;
    }
    ne_add_request_header(req, "Depth", value);
}
