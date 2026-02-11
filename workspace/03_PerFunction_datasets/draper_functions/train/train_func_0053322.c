OnMotion ()
{
	m_pData->UnselectAll ();
	bool allowed = false;
	if (m_pObject)
		switch (m_pObject->GetType ()) {
		case gcu::FragmentType:
			m_pObject = static_cast <gcp::Fragment *> (m_pObject)->GetAtom ();
		case gcu::AtomType:
			allowed = AllowAsSource (reinterpret_cast <gcp::Atom *> (m_pObject));
			break;
		case gcu::BondType:
			allowed = AllowAsSource (reinterpret_cast <gcp::Bond *> (m_pObject));
			break;
		default:
			if (m_pObject->GetType () == gcp::ElectronType) {
				if (m_Full)
					allowed = static_cast <gcp::Electron *> (m_pObject)->IsPair ();
				else
					allowed = true;
			} else if (m_pObject->GetType () == gcp::MechanismArrowType) {
				if (m_Full)
					allowed = static_cast <gcp::MechanismArrow *> (m_pObject)->GetPair ();
				else
					allowed = !static_cast <gcp::MechanismArrow *> (m_pObject)->GetPair ();
				if (allowed)
					static_cast <gccv::BezierArrow *> (dynamic_cast <gccv::ItemClient *> (m_pObject)->GetItem ())->SetShowControls (true);
			}
			break;
		}
	if (allowed)
		m_pData->SetSelected (m_pObject);
	gdk_window_set_cursor (gtk_widget_get_parent_window (m_pWidget), allowed? m_pApp->GetCursor (gcp::CursorPencil): m_pApp->GetCursor (gcp::CursorUnallowed));
}
