OnClicked ()
{
	m_pData->UnselectAll ();
	if (m_pObject) {
		if (m_pObject->IsLocked ())
			return false;
		TypeId Id = m_pObject->GetType ();
		if (Id == ReactionOperatorType)
			return false;
		gccv::ItemClient *client = dynamic_cast <gccv::ItemClient *> (m_pObject);
		if (client) {
			client->SetSelected (gcp::SelStateErasing);
			m_Item = client->GetItem ();
		}
		if (Id == AtomType) {
			Object* parent = m_pObject->GetParent ();
			if (parent->GetType () == FragmentType)
				m_Item = dynamic_cast <gccv::ItemClient *> (parent)->GetItem ();
			std::map<Atom*, Bond*>::iterator i;
			gcp::Bond* pBond = (gcp::Bond*)((gcp::Atom*)m_pObject)->GetFirstBond (i);
			while (pBond) {
				pBond->SetSelected (gcp::SelStateErasing);
				pBond = (gcp::Bond*) ((gcp::Atom*) m_pObject)->GetNextBond (i);
			}
		}
		m_bChanged = true;
		return true;
	}
	return false;
}
