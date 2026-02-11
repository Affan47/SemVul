startModel() {
	if (!hasWitness_) {
		startObject("Witnesses", type_array);
		hasWitness_ = true;
	}
	if (hasModel_) {
		endObject();
		hasModel_ = false;
	}
	startObject();
	hasModel_ = true;
}
