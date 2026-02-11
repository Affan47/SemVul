getDescriptionAsText(std::ostream &o) const
{
	CObservation::getDescriptionAsText(o);

	std::cout << format("Measured Power: %.02f/100\n", power);
}
