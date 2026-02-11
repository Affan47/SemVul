RemoveAtom (Atom* pAtom)
{
	std::map<gcu::Atom*, gcu::Bond*>::iterator i;
	Bond* pBond;
	while ((pBond = (Bond*) pAtom->GetFirstBond (i)))
	{

		if (!m_bUndoRedo && !m_bIsLoading && m_pCurOp && dynamic_cast <DeleteOperation *> (m_pCurOp))
			m_pCurOp->AddObject (pBond);
		RemoveBond (pBond);
	}
	Molecule *pMol = (Molecule*) pAtom->GetMolecule ();
	delete pMol;
	m_pView->Remove (pAtom);
	delete pAtom;
}
