setDefaults()
{
    static char buff[100];
    char *myenv;


    printerCheck->set();


    if ((myenv = getenv("PRINTER")) != 0)
	sprintf(buff, "lpr -P%s", myenv);
    else
	strcpy(buff, "lpr");
    commandInput->value((const char *)buff);


    sprintf(buff, "%s.ps", appName);
    filenameInput->value(buff);


    landscapeCheck->set();


    A4Check->set();


    linesCheck->set();


    nbcopiesInput->value("1");


    whichPanel = SPECTRAPANEL;


    return;
}
