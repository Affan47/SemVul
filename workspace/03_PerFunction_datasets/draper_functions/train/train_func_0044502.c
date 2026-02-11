Qoutput()
{
    if ((srcon0.value.get() & (SRCON0::SRLEN | SRCON0::SRQEN)) ==
	(SRCON0::SRLEN | SRCON0::SRQEN))
    {
	if (!m_SRQsource)
	    m_SRQsource = new PeripheralSignalSource(SRQ_pin);

	SRQ_pin->setSource(m_SRQsource);
	SRQ_pin->getPin().newGUIname("SRQ");
    }
    else
    {
	SRQ_pin->setSource(0);
	if (strcmp("SRQ", SRQ_pin->getPin().GUIname().c_str()) == 0)
	{
	    SRQ_pin->getPin().newGUIname(SRQ_pin->getPin().name().c_str());
	}
    }
}
