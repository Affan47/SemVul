byConnectorCount(MissingSvgInfo & m1, MissingSvgInfo & m2)
{
    if (m1.connectorSvgIds.count() == m2.connectorSvgIds.count() && m1.modelPart != m2.modelPart) {
        m1.equal = m2.equal = true;
    }

	return (m1.connectorSvgIds.count() > m2.connectorSvgIds.count());
}
