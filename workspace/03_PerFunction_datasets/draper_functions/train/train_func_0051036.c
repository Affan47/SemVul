processDialog(void)
{
	int retval = Dialog::GUI_CONTINUE;
	switch(state) {
		case STATE_MAIN:
			retval = processDialogMain();
			break;
		case STATE_CDI0:
			retval = processDialogCdi0();
			break;
		case STATE_CDI1:
			retval = processDialogCdi1();
			break;
	}
	return retval;
}
