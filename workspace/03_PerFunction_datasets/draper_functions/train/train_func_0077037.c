setPins(PinModule *sri, PinModule *srq, PinModule *srnq)
{

    if(!SRI_pin)
    {
	m_SRinSink = new SRinSink(this);
	sri->addSink(m_SRinSink);
    }
    else if (SRI_pin != sri)
    {
	SRI_pin->removeSink(m_SRinSink);
	sri->addSink(m_SRinSink);
    }
    SRI_pin = sri;
	SRQ_pin = srq;
	SRNQ_pin = srnq;

}
