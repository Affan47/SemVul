SetChargePosition (unsigned char Pos, bool def, double angle, double distance)
{
	if (Pos != m_ChargePos) {
		m_ChargeAutoPos = def;
		if (m_ChargePos > 0)
			NotifyPositionOccupation (m_ChargePos, false);
		m_ChargePos = Pos;
		if (m_ChargePos > 0)
			NotifyPositionOccupation (m_ChargePos, true);
	}
	m_ChargeAngle = angle;
	m_ChargeDist = distance;
	m_AvailPosCached = false;
}
