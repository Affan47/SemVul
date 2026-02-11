xmlParserGenericErrorFunc(void *  , const char* msg, ...) {
	XML_Generic_error_info* p;

	if(!(p=xml_generic_error_info))
		p=xml_generic_error_info=new(PointerFreeGC) XML_Generic_error_info;

	va_list args;
	va_start(args, msg);
	p->used+=vsnprintf(p->buf+p->used, sizeof(p->buf)-p->used, msg, args);
	va_end(args);
}
