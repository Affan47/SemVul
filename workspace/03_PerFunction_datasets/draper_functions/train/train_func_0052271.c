create_aligner(ElementT *e, RouterT *, ErrorHandler *)
{
    Vector<String> args;
    cp_argvec(e->configuration(), args);
    unsigned offset = 0;


    if (cp_va_kparse(args, ErrorHandler::silent_handler(), "OFFSET", cpkP, cpUnsigned, &offset, cpIgnoreRest, cpEnd) < 0)
	(void) cp_va_kparse(args, ErrorHandler::silent_handler(), "BADSRC*", cpkP, cpIgnore, "OFFSET", cpkP, cpUnsigned, &offset, cpIgnoreRest, cpEnd);
    return new WantAligner(Alignment(4, 0) - (int)offset);
}
