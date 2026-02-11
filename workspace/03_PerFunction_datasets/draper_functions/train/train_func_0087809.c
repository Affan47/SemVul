saveInstanceLocation(QXmlStreamWriter & streamWriter)
{
	streamWriter.writeAttribute("x", QString::number(m_viewGeometry.loc().x()));
	streamWriter.writeAttribute("y", QString::number(m_viewGeometry.loc().y()));
	streamWriter.writeAttribute("wireFlags", QString::number(m_viewGeometry.flagsAsInt()));
	GraphicsUtils::saveTransform(streamWriter, m_viewGeometry.transform());
}
