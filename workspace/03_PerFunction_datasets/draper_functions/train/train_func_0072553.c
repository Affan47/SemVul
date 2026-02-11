CheckIfAllowed ()
{

	gcp::Atom* pAtom[m_size];
	gccv::Item *item;
	gccv::Canvas *canvas = m_pView->GetCanvas ();
	Object* pObject, *group, *other;
	gcp::Document *pDoc = m_pView->GetDoc ();
	group = (m_pObject)? m_pObject->GetMolecule ()->GetParent (): NULL;
	if (group == pDoc)
		group = NULL;
	int i, n;
	for (i = 0; i < m_size; i++) {
		m_x = m_Points[i].x;
		m_y = m_Points[i].y;
		item = canvas->GetItemAt (m_x, m_y);
		pObject = (item)? dynamic_cast <Object *> (item->GetClient ()): NULL;
		if (gcp::MergeAtoms && pObject) {
			TypeId Id = pObject->GetType ();
			switch (Id) {
				case BondType:
				case FragmentType:
					pAtom[i] = (gcp::Atom*) pObject->GetAtomAt (m_x / m_dZoomFactor, m_y / m_dZoomFactor);
					break;
				case AtomType:
					pAtom[i] = (gcp::Atom*) pObject;
					break;
				default:
					pAtom[i] = NULL;
			}
		} else
			pAtom[i] = NULL;
	}
	for (i = 0; i < m_size; i++) {
		if (!pAtom[i])
			continue;
		other = pAtom[i]->GetMolecule ()->GetParent ();
		if (other != pDoc) {
			if (group == NULL)
				group = other;
			else if (other != group)
				return false;
		}
		n = 0;
		if (!pAtom[i]->GetBond (pAtom[(i)? i - 1: m_size -1]))
			n++;
		if (!pAtom[i]->GetBond (pAtom[(i < m_size - 1)? i + 1: 0]))
			n++;
		if (n && (!pAtom[i]->AcceptNewBonds (n)))
			return false;
		pAtom[i]->GetCoords (&m_Points[i].x, &m_Points[i].y);
		m_Points[i].x *= m_dZoomFactor;
		m_Points[i].y *= m_dZoomFactor;
	}
	return true;
}
