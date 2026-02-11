AllowAsSource (gcp::Bond *bond)
{
	std::set <gcu::Object *>::iterator i;
	gcu::Object* obj = bond->GetFirstLink (i);
	while (obj && obj->GetType () != gcp::MechanismArrowType)
		obj = bond->GetNextLink (i);
	if (obj) {
		if (m_Full)
			return false;

		gcp::MechanismArrow *arrow = static_cast <gcp::MechanismArrow *> (obj);
		if (arrow->GetPair () || arrow->GetSource () != bond)
			return false;

		obj = bond->GetNextLink (i);
		if (obj && obj->GetType () == gcp::MechanismArrowType)
			return false;
	}
	return true;
}
