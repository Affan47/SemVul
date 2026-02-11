timestamp_data_handler(int op, String &str, Element *element, const Handler *h, ErrorHandler *errh)
{
    Timestamp *ptr = reinterpret_cast<Timestamp *>(reinterpret_cast<uintptr_t>(element) + reinterpret_cast<uintptr_t>(h->user_data(op)));
    if (op == Handler::h_read) {
	str = ptr->unparse();
	return 0;
    } else if (cp_time(str, ptr))
	return 0;
    else
	return errh->error("expected timestamp");
}
