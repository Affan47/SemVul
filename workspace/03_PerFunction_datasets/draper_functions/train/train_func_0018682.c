configure(Vector<String> &conf, ErrorHandler *errh)
{
    String message, type = "MESSAGE";
    if (Args(conf, this, errh)
	.read_mp("MESSAGE", message)
	.read_p("TYPE", KeywordArg(), type).complete() < 0)
	return -1;
    const char *err;
    if (type == "MESSAGE")
	err = ErrorHandler::e_info;
    else if (type == "WARNING")
	err = ErrorHandler::e_warning_annotated;
    else if (type == "ERROR")
	err = ErrorHandler::e_error;
    else
	return errh->error("unrecognized message type");
    return errh->xmessage(err, message);
}
