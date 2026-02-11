init(void)
{
	if (this->checkColorUsability())
		mode = SVUT_OUT_STD_COLOR;
	else
		mode = SVUT_OUT_STD_BW;
	displaySuccess = false;
	displayDetails = true;
	action = SVUT_ACTION_RUN_TESTS;
	filename = "";
	outputStream = NULL;
	externalOutputStream = NULL;
}
