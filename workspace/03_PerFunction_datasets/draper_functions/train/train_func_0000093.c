operator()(Actor* self, bool force) {
	if (self->getExp() >= 1 && self->getHealth() < self->getMaxHealth()) {
		self->addExp(-1); self->hurt(-3);
		self->msgs.push_back("You feel a bit better.");
		return true;
	}
	return false;
}
