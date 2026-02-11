answerPhoneCmd(AnswerType atype, const char* dialnumber)
{
    CallType ctype = ClassModem::CALLTYPE_UNKNOWN;
    if (state == LISTENING) {


	Dispatcher::instance().stopTimer(&answerHandler);
	answerPhone(atype, ctype, received_callid, dialnumber);
    } else if (lockModem()) {


	sendModemStatus("B");
	answerPhone(atype, ctype, received_callid, dialnumber);
    } else if (state != ANSWERING && state != RECEIVING) {


	discardModem(false);
	changeState(LOCKWAIT, pollLockWait);
	sendModemStatus("U");
    }
}
