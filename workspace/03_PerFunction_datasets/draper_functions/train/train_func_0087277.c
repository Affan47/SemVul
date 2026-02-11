setXONXOFF(FlowControl iFlow, FlowControl oFlow, SetAction act)
{
    traceModemOp("set XON/XOFF/%s: input %s, output %s",
	actNames[act],
	iFlow == ClassModem::FLOW_NONE ? "ignored" : "interpreted",
	oFlow == ClassModem::FLOW_NONE ? "disabled" : "generated"
    );
    struct termios term;
    if (!tcgetattr("setXONXOFF", term))
	return (false);
    setFlow(term, iFlow, oFlow);
    if (act == ClassModem::ACT_FLUSH)
	flushModemInput();
    return (tcsetattr(actCode[act], term));
}
