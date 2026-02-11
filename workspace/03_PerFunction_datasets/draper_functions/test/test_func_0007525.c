setDefaults(GLENumberFormatter* def) {
	if (def->hasPrefix()) setPrefix(def->getPrefix());
	if (def->hasNoZeroes()) setNoZeroes(true);
	if (def->hasSign()) setSign(true);
	if (def->hasPadLeft()) setPadLeft(def->getPadLeft());
	if (def->hasPadRight()) setPadRight(def->getPadRight());
}
