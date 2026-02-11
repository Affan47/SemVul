ConnectAssociation(Association* assoc, int lossy) {
	CONDITION cond;

	cond = ASC_ConnectAssociation(
						assoc,
						assoc->m_calledAET,
						assoc->m_calledPeer,
						assoc->m_calledPort,
						assoc->m_ourAET,
						assoc->m_abstractSyntax,
						lossy);

	if (!SUCCESS(cond)) {
		assoc->Drop(cond);
		return cond;
	}

	assoc->dcmNet = this;
	assoc->msgId = assoc->assoc->nextMsgID;

	return cond;
}
