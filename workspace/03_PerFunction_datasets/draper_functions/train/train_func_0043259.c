handleInterrupt(void)
{
    bool result;


    debugOut("INTERRUPT\n");
    unsigned int intrSP = readSP();
    unsigned int retPC = readBWord(intrSP + 1) << 1;
    debugOut("INT SP = %x, retPC = %x\n", intrSP, retPC);

    bool needBP = !theJtagICE->codeBreakpointAt(retPC);

    for (;;)
    {
	if (needBP)
	{


	    if (!theJtagICE->addBreakpoint(retPC, CODE, 0))
		return false;
	}
	result = theJtagICE->jtagContinue();
	if (needBP)
	    theJtagICE->deleteBreakpoint(retPC, CODE, 0);

	if (!result || !needBP)
	    break;


	if (readSP() > intrSP)
	    break;
    }
    return result;
}
