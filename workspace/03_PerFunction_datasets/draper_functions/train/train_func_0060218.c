command() {
	switch (_sequence) {
	case 0:
		return _do_call;

	case 1:
		return _call_individual;

	case 2:
		return _call_item;

	case 3:
		Inventory::update();
		return _set_call;

	default:
		return Action::NOOP;
	}
}
