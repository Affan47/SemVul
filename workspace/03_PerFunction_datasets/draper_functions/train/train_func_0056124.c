initialize(ErrorHandler *errh)
{

    if (!output_is_push(0))
	_notifier.initialize(Notifier::EMPTY_NOTIFIER, router());

    if (_ff.initialize(errh) < 0)
	return -1;


    String line;
    if (_ff.peek_line(line, errh, true) < 0)
	return -1;
    else if (!line || !isdigit((unsigned char) line[0]))
	errh->lwarning(_ff.print_filename(), "first line suspicious; is this a tcpdump output file?");

    _format_complaint = false;
    if (output_is_push(0))
	ScheduleInfo::initialize_task(this, &_task, _active, errh);
    return 0;
}
