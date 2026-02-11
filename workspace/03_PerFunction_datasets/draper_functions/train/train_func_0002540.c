charset_from_utf8(Octstr *utf8, Octstr **to, Octstr *charset_to)
{
    int ret;
    xmlCharEncodingHandlerPtr handler = NULL;
    xmlBufferPtr frombuffer = NULL;
    xmlBufferPtr tobuffer = NULL;

    handler = xmlFindCharEncodingHandler(octstr_get_cstr(charset_to));
    if (handler == NULL)
	return -2;


    tobuffer = xmlBufferCreate();
    frombuffer = xmlBufferCreate();
    xmlBufferAdd(frombuffer, (unsigned char*)octstr_get_cstr(utf8), octstr_len(utf8));

    ret = xmlCharEncOutFunc(handler, tobuffer, frombuffer);
    if (ret < -2)


	ret = -1;

    *to = octstr_create_from_data((char*)tobuffer->content, tobuffer->use);


    xmlBufferFree(tobuffer);
    xmlBufferFree(frombuffer);

    return ret;
}
