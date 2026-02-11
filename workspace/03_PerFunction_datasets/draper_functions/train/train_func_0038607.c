operator()(const BodyNodeP& n, NodeId atomId, uint32 idx) const {
	assert(n.node->extended() && n.node->get_pred(idx) == atomId); (void)atomId;
	ExtData* ext = self->extended_[self->bodies_[n.id].lower_or_ext];
	ext->removeFromWs(idx, n.node->pred_weight(idx, false));
	if (ext->lower > 0 && self->bodies_[n.id].watches > 0) {


		self->forwardUnsource(n, true);
	}
}
