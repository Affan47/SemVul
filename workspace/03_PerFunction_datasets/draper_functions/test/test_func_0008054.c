clientGotNotEnough(clientHttpRequest * http)
{
    squid_off_t cl = httpReplyBodySize(http->request->method, http->entry->mem_obj->reply);
    int hs = http->entry->mem_obj->reply->hdr_sz;
    if (cl < 0)
	return 0;
    if (http->out.offset != cl + hs)
	return 1;
    return 0;
}
