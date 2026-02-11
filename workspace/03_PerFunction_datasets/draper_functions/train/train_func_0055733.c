updateResistances(QString r) {
	if (!Resistances.contains(r + OhmSymbol)) {
		Resistances.append(r + OhmSymbol);
	}
}
