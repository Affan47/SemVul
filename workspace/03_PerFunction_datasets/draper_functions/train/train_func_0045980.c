ChangedDisplay3D ()
{
	if (!m_Mol)
		return;
	std::list <Atom *>::const_iterator i;
	Atom const *atom = m_Mol->GetFirstAtom (i);
	unsigned int Z;
	gdouble R, w, x, y, z;
	GcuAtomicRadius rad;
	rad.type = GCU_VAN_DER_WAALS;
	rad.charge = 0;
	rad.cn = -1;
	rad.spin = GCU_N_A_SPIN;
	rad.scale = NULL;
	m_MaxDist = 0;
	while (atom) {
		Z = atom->GetZ ();
		if (Z > 0) {
			if (m_Display3D == CYLINDERS) {
				R = 12.;
			} else if (m_Display3D == WIREFRAME) {
				R = 0.;
			} else {
				rad.Z = Z;
				Element::GetElement (Z)->GetRadius (&rad);
				R = rad.value.value;
				if (m_Display3D == BALL_AND_STICK)
					R *= 0.2;
			}
			atom->GetCoords (&x, &y, &z);
			if ((w = sqrt (x * x + y * y + z * z)) > m_MaxDist - R)
				m_MaxDist = w + R;
		}
		atom = m_Mol->GetNextAtom (i);
	}
}
