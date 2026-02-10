CompressionWiggleIterator(WiggleIterator * i) {
	if (i->overlaps)
		return i;
	else {
		UnaryWiggleIteratorData * data = (UnaryWiggleIteratorData *) calloc(1, sizeof(UnaryWiggleIteratorData));
		data->iter = i;
		return newWiggleIterator(data, &CompressionWiggleIteratorPop, &UnaryWiggleIteratorSeek, i->default_value);
	}
}
