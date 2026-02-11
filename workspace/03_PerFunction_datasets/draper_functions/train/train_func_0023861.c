addedToScene(bool temporary)
{
	if (this->scene()) {
		QString temp = m_size;
		m_size = "";
		setProp("size", temp);
	}
    return Capacitor::addedToScene(temporary);
}
