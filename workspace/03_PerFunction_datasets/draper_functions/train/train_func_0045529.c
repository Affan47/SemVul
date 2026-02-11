ReloadData ()
{
	if (m_Closing)
		return;
	gcr_grid_delete_all (GCR_GRID (m_Grid));
	m_Atoms.clear ();
	gcr::AtomList* Atoms = m_pDoc->GetAtomList ();
	for (list < Atom * >::iterator i = Atoms->begin (); i != Atoms->end (); i++)
		m_Atoms[gcr_grid_append_row (GCR_GRID (m_Grid), ((*i)->GetZ ())? Element::Symbol ((*i)->GetZ ()): _("Unknown"),
	                                        (*i)->x (), (*i)->y (), (*i)->z ())] = *i;
	if (!m_Atoms.size ())
		gtk_widget_set_sensitive (DeleteAllBtn, false);
}

}
