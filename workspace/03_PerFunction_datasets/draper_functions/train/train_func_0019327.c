InitODEForMode(EODEINITMODE imInitMode)
{
	bool bResult = false;

#if dOU_ENABLED
	bool bOUCustomizationsDone = false;
#endif
#if dATOMICS_ENABLED
	bool bAtomicsInitialized = false;
#endif
#if dTLS_ENABLED
	EODETLSKIND tkTLSKindToInit = g_atkTLSKindsByInitMode[imInitMode];
	bool bTlsInitialized = false;
#endif

	do
	{
		bool bAnyModeAlreadyInitialized = IsODEAnyModeInitialized();

		if (!bAnyModeAlreadyInitialized)
		{
#if dOU_ENABLED
			if (!COdeOu::DoOUCustomizations())
			{
				break;
			}

			bOUCustomizationsDone = true;
#endif

#if dATOMICS_ENABLED
			if (!COdeOu::InitializeAtomics())
			{
				break;
			}

			bAtomicsInitialized = true;
#endif
		}

#if dTLS_ENABLED
		if (!COdeTls::Initialize(tkTLSKindToInit))
		{
			break;
		}

		bTlsInitialized = true;
#endif

		if (!bAnyModeAlreadyInitialized)
		{
#if dTRIMESH_ENABLED && dTRIMESH_OPCODE
			if (!Opcode::InitOpcode())
			{
				break;
			}
#endif

#if dTRIMESH_ENABLED && dTRIMESH_GIMPACT
			gimpact_init();
#endif

			dInitColliders();
		}

		bResult = true;
	}
	while (false);

	if (!bResult)
	{
#if dTLS_ENABLED
		if (bTlsInitialized)
		{
			COdeTls::Finalize(tkTLSKindToInit);
		}
#endif

#if dATOMICS_ENABLED
		if (bAtomicsInitialized)
		{
			COdeOu::FinalizeAtomics();
		}
#endif

#if dOU_ENABLED
		if (bOUCustomizationsDone)
		{
			COdeOu::UndoOUCustomizations();
		}
#endif
	}

	return bResult;
}
