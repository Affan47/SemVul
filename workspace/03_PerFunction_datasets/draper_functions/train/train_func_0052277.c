getFlowCmd(FlowControl f) const
{
    if (f == ClassModem::FLOW_RTSCTS)
	return (hardFlowCmd);
    else if (f == ClassModem::FLOW_XONXOFF)
	return (softFlowCmd);
    else if (f == ClassModem::FLOW_NONE)
	return (noFlowCmd);
    else
	return (fxStr::null);
}
