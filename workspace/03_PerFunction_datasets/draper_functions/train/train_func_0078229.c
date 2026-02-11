Transform2D (Matrix2D& m, double x, double y)
{
	gcu::Atom::Transform2D (m, x, y);

	map<string, Object*>::iterator i;
	Object* electron = GetFirstChild (i);
	while (electron) {
		electron->Transform2D (m, x, y);
		electron = GetNextChild (i);
	}
	if (GetCharge ()) {
		if (m_ChargeAutoPos) {
			if (m_ChargePos > 0)
				NotifyPositionOccupation (m_ChargePos, false);
			m_ChargePos = 0xff;
			Update ();
		} else {
			double xc = cos (m_ChargeAngle), yc = - sin (m_ChargeAngle);
			m.Transform (xc, yc);
			m_ChargeAngle = atan2 (- yc, xc);
			if (m_ChargeAngle < 0)
				m_ChargeAngle += 2 * M_PI;
			SetChargePosition (0, FALSE, m_ChargeAngle, m_ChargeDist);
		}
	}
}
