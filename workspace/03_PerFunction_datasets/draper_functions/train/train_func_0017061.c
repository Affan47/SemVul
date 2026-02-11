GetProperty (unsigned property) const
{
	ostringstream res;
	switch (property) {
	case GCU_PROP_BOND_BEGIN:
		res << m_Begin->GetId ();
		break;
	case GCU_PROP_BOND_END:
		res << m_End->GetId ();
		break;
	case GCU_PROP_BOND_ORDER:
		res << static_cast <unsigned> (m_order);
		break;
	default:
			return Object::GetProperty (property);
	}
	return res.str ();
}
