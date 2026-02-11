initSplit ( TSplitVar* split )
{

	TSplitVar::iterator p = split->begin(), p_end = split->end();
	SigSet impSet = buildSet ( p->sig, p->name );
	BipolarPointer bp = split->C->pBody+1;
	while ( ++p != p_end )
	{
		if ( p->Module.size() == 1 )
			addSplitRule ( buildSet ( p->sig, p->name ), impSet, bp );
		else
		{

			std::set<TSignature> Out;

			SigVec Allowed;

			AxiomVec Module ( p->Module.begin(), p->Module.end() );

			TSignature sig = p->sig;
			prepareStartSig ( Module, sig, Allowed );

			BuildAllSeedSigs ( Allowed, sig, Module, Out );
			for ( std::set<TSignature>::const_iterator q = Out.begin(), q_end = Out.end(); q != q_end; ++q )
				addSplitRule ( buildSet ( *q, p->name ), impSet, bp );
		}
	}
}
