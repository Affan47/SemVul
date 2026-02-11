sendSetup(FaxRequest& req, const Class2Params& dis, Status& eresult)
{
    const char* cmdFailed = " (modem command failed)";


    if (req.passwd != "" && pwCmd != "" && !class2Cmd(pwCmd, req.passwd)) {
	eresult = Status(204, "Unable to send password%s", cmdFailed);
	return (false);
    }
    if (req.subaddr != "" && saCmd != "" && !class2Cmd(saCmd, req.subaddr)) {
	eresult = Status(205, "Unable to send subaddress%s", cmdFailed);
	return (false);
    }
    if (minsp != BR_2400 && !class2Cmd(minspCmd, minsp)) {
	eresult = Status(206, "Unable to restrict minimum transmit speed to %s%s",
	    Class2Params::bitRateNames[req.minbr], cmdFailed);
	return (false);
    }
    if (conf.class2DDISCmd != "") {
	if (!class2Cmd(conf.class2DDISCmd, dis, false)) {
	    eresult = Status(207, "Unable to setup session parameters "
			 "prior to call%s", cmdFailed);
	    return (false);
	}
	params = dis;
    }
    hadHangup = false;
    return (FaxModem::sendSetup(req, dis, eresult));
}
