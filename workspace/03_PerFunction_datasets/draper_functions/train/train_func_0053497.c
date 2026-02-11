SetPhase(TIndex pos,TData newPhase)
{
	SpecTypeFlags tmpFlags;
	GetType(tmpFlags);
	if(tmpFlags.bMagPhase)
		GetPhaseBuffer()[pos]=newPhase;
	else if (tmpFlags.bMagPhaseBPF)
		GetPhaseBPF().SetValue(pos,newPhase);
	else if (tmpFlags.bPolar)
		GetPolarArray()[pos].SetAng(newPhase);
	else if (tmpFlags.bComplex){
		TData tmpMag=GetComplexArray()[pos].Mag();
		GetComplexArray()[pos].SetReal(tmpMag*CLAM_cos(newPhase));
		GetComplexArray()[pos].SetImag(tmpMag*CLAM_sin(newPhase));
	}
}
