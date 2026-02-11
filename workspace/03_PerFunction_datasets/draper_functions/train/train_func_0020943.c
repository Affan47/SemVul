addedToScene(bool temporary)
{
	if (this->scene()) {
		setResistance(m_ohms, m_pinSpacing, true);
	}

    return Capacitor::addedToScene(temporary);
}
