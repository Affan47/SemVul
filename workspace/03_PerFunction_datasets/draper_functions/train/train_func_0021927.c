SetBPFSize(int s)
{
	if (s != GetprSize()) {
		AddprBPFSize();
		UpdateData();
		SetprBPFSize(s);
	}
	else {
		RemoveprBPFSize();
		UpdateData();
	}

	if (HasMagBPF() && HasPhaseBPF())
	{
		GetMagBPF().Resize(s);
		GetMagBPF().SetSize(s);
		GetPhaseBPF().Resize(s);
		GetPhaseBPF().SetSize(s);
	}
}
