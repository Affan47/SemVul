findAnswer(const char* s)
{
    static const AnswerMsg answer[2] = {
    { "CONNECT ", 8,
      FaxModem::AT_NOTHING, FaxModem::OK, FaxModem::CALLTYPE_DATA },
    { "CONNECT",  7,
      FaxModem::AT_NOTHING, FaxModem::OK, FaxModem::CALLTYPE_UNKNOWN },
    };
    return strneq(s, answer[0].msg, answer[0].len) ? &answer[0] :
	   strneq(s, answer[1].msg, answer[1].len) ? &answer[1] :
	      FaxModem::findAnswer(s);
}
