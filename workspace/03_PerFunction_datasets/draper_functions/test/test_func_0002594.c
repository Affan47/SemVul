writer (void *closure, const unsigned char *data, unsigned int length)
{
    if (length == gvwrite((GVJ_t *)closure, (const char*)data, length))
	return CAIRO_STATUS_SUCCESS;
    return CAIRO_STATUS_WRITE_ERROR;
}
