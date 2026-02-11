enableLimitsQ(bool &enable) {

	char response[150];

	if (!transmit("L") || !receive("L",response)) return false;

    if (strstr( upperCase(response).c_str(),"ENABLE")!=NULL) enable=true;
	else enable=false;

	return true;
}
