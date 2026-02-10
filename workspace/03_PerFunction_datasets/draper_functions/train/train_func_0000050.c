uih_command(struct uih_context *uih, const char *command)
{
    errstring = NULL;
    uih->playpos = 0;
    uih->playstring = command;
    uih_processcommand(uih, (uih->play ? MENUFLAG_NOMENU : 0));
    uih->playstring = NULL;
    if (errstring != NULL) {
	uih_error(uih, errstring);
    }
}
