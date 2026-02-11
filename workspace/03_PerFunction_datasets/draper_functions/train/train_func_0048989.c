removeInteractionInfos()
{
	for (int i=0; i<8;i++) {
		delete m_interactionInfos[i];
		m_interactionInfos[i] = NULL;
	}
}
