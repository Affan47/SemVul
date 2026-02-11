LoadData (char const *data, char const *mime_type, size_t size)
{
	bool need_free = false;
	if (!mime_type) {
		mime_type = go_get_mime_type_for_data (data, size);
		need_free = true;
	}
	if (!mime_type) {

		return ContentTypeUnknown;
	}
	if (size == 0)
		size = strlen (data);
	GsfInput *input = gsf_input_memory_new (reinterpret_cast <guint8 const *> (data), size, false);

	Application *app = GetApp ();
	Object *obj = app->CreateObject ("atom", this);
	if (obj)
		delete obj;
	else {
		gcu::Loader::Init (app);
		app->AddType ("atom", CreateAtom, AtomType);
		app->AddType ("bond", CreateBond, BondType);
		app->AddType ("molecule", CreateMolecule, MoleculeType);
	}
	Clear ();
	ContentType type = app->Load (input, mime_type, this);
	Loaded ();
	if (type == ContentType3D) {

		std::map<std::string, Object*>::iterator it;
		obj =  GetFirstChild (it);
		while (obj) {
			m_Mol = dynamic_cast <Molecule *> (obj);
			if (m_Mol)
				break;
			obj = GetNextChild (it);
		}

		double x0, y0, z0;
		x0 = y0 = z0 = 0.0;
		std::list <Atom *>::const_iterator i;
		Atom const *atom = m_Mol->GetFirstAtom (i);
		while (atom) {
			x0 += atom->x ();
			y0 += atom->y ();
			z0 += atom->z ();
			atom = m_Mol->GetNextAtom (i);
		}
		m_Mol->Move (-x0 / m_Mol->GetAtomsNumber (), -y0 / m_Mol->GetAtomsNumber (), -z0 / m_Mol->GetAtomsNumber ());
		char const *title = m_Mol->GetName ();
		if (title)
			SetTitle (title);
		ChangedDisplay3D ();
		m_View->Update ();
	} else if (type != ContentTypeUnknown) {
		Clear ();

	}
	if (need_free)
		g_free (const_cast <char *> (mime_type));
	g_object_unref (input);
	return type;
}
