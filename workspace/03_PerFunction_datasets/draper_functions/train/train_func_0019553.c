computeEnvelopeInternal() const
{
	if (isEmpty()) {
		return Envelope::AutoPtr(new Envelope());
	}

	return Envelope::AutoPtr(new Envelope(getCoordinate()->x,
			getCoordinate()->x, getCoordinate()->y,
			getCoordinate()->y));
}
