GetConfig(SpectrumConfig& c) const
{
	SpecTypeFlags f;

	f.bMagPhaseBPF = HasMagBPF() && HasPhaseBPF();
	f.bMagPhase = HasMagBuffer() && HasPhaseBuffer();
	f.bPolar = HasPolarArray();
	f.bComplex = HasComplexArray();

	c.SetType(f);
	c.SetSize( GetSize() );
	c.SetSpectralRange(GetSpectralRange());
	c.SetScale(GetScale());

	if (GetBPFSize()<0 || GetBPFSize()==GetSize()) {
		c.RemoveBPFSize();
		c.UpdateData();
	}
	else
	{
		c.AddBPFSize();
		c.UpdateData();
		c.SetBPFSize( GetBPFSize() );
	}
}
