HasImplicitElectronPairs ()
{
	map<string, Object*>::iterator i;
	Object *obj = GetFirstChild (i);
	Electron* electron = NULL;
	if (m_Valence > 0) {
		int nexplp = 0;
		while (obj) {
			electron = dynamic_cast <Electron *> (obj);
			if (electron && electron->IsPair ())
				nexplp++;
			obj = GetNextChild (i);
		}
		return (m_nlp > nexplp);
	}
	unsigned nel = 0;
	while (electron) {
		electron = dynamic_cast <Electron *> (obj);
		if (electron) {
			if (electron->IsPair ())
				nel += 2;
			else
				nel++;
		}
		obj = GetNextChild (i);
	}
	nel += GetTotalBondsNumber ();
	int nocc = GetChildrenNumber () + GetTotalBondsNumber ();
	return (nocc < m_ValenceOrbitals) && (((m_Element->GetValenceElectrons() - m_Charge) > nel + 1) || m_ChargeAuto);
}
