SynchronizeTo(const SpecTypeFlags& tmpFlags,const Spectrum& in)
{


	SpecTypeFlags currentFlags;
	GetType(currentFlags);
	int size = GetSize();

	if(tmpFlags.bMagPhase)
	{
		if(currentFlags.bPolar) MagPhase2Polar(in);
		if(currentFlags.bComplex) MagPhase2Complex(in);
		if(currentFlags.bMagPhaseBPF) MagPhase2BPF(in);
	}
	else if(tmpFlags.bComplex)
	{
		if(currentFlags.bPolar)  Complex2Polar(in);
		if(currentFlags.bMagPhase) Complex2MagPhase(in);
		if(currentFlags.bMagPhaseBPF)
		{
			if(currentFlags.bMagPhase) MagPhase2BPF();
			else
			{
				AddMagBuffer();
				AddPhaseBuffer();
				UpdateData();
				GetMagBuffer().Resize(size);
				GetPhaseBuffer().Resize(size);
				GetMagBuffer().SetSize(size);
				GetPhaseBuffer().SetSize(size);
				Complex2MagPhase(in);
				MagPhase2BPF();

				RemoveMagBuffer();
				RemovePhaseBuffer();
				UpdateData();
			}
		}
	}
	else if(tmpFlags.bPolar)
	{
		if(currentFlags.bComplex)  Polar2Complex(in);
		if(currentFlags.bMagPhase) Polar2MagPhase(in);
		if(currentFlags.bMagPhaseBPF)
		{
			if(currentFlags.bMagPhase) MagPhase2BPF();
			else
			{
				AddMagBuffer();
				AddPhaseBuffer();
				UpdateData();
				GetMagBuffer().Resize(size);
				GetPhaseBuffer().Resize(size);
				GetMagBuffer().SetSize(size);
				GetPhaseBuffer().SetSize(size);
				Polar2MagPhase(in);
				MagPhase2BPF();

				RemoveMagBuffer();
				RemovePhaseBuffer();
				UpdateData();
			}
		}
	}
	else if(tmpFlags.bMagPhaseBPF)
	{
		bool deleteMagPhase=false;
		if(!currentFlags.bMagPhase)
		{
			deleteMagPhase=true;
			AddMagBuffer();
			AddPhaseBuffer();
			UpdateData();
			GetMagBuffer().Resize(size);
			GetPhaseBuffer().Resize(size);
			GetMagBuffer().SetSize(size);
			GetPhaseBuffer().SetSize(size);
		}
		BPF2MagPhase(in);

		if(currentFlags.bPolar) MagPhase2Polar();
		if(currentFlags.bComplex) MagPhase2Complex();
		if(deleteMagPhase)
		{
			RemoveMagBuffer();
			RemovePhaseBuffer();
			UpdateData();
		}
	}


}
