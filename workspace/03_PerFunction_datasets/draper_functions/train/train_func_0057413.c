SetTypeSynchronize(const SpecTypeFlags& newFlags)
{
	SpecTypeFlags previousFlags;
	GetType(previousFlags );
	SpecTypeFlags tmpFlags;

	tmpFlags.bComplex = previousFlags.bComplex | newFlags.bComplex;
	tmpFlags.bPolar = previousFlags.bPolar | newFlags.bPolar;
	tmpFlags.bMagPhase = previousFlags.bMagPhase | newFlags.bMagPhase;
	tmpFlags.bMagPhaseBPF = previousFlags.bMagPhaseBPF | newFlags.bMagPhaseBPF;

	SetType(tmpFlags);
	SynchronizeTo(previousFlags);
	SetType(newFlags);
}
