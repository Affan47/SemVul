sa_payload_create_from_proposals_v2(linked_list_t *proposals)
{
	private_sa_payload_t *this;
	enumerator_t *enumerator;
	proposal_t *proposal;

	this = (private_sa_payload_t*)sa_payload_create(PLV2_SECURITY_ASSOCIATION);
	enumerator = proposals->create_enumerator(proposals);
	while (enumerator->enumerate(enumerator, &proposal))
	{
		add_proposal_v2(this, proposal);
	}
	enumerator->destroy(enumerator);

	return &this->public;
}
