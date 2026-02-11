operator<<(std::ostream &ostr, Medium* item)
{
	return ostr << " "
			<< setw(8) << right << item->getSignature() << "   "
			<< setw(6) << left << item->getType() << "   "
			<< setw(20) << left << item->getTitle().substr(0, 20) << "   "
			<< setw(6) << left << item->printState() << "   "
			<< item->getDetails()
			<< endl;
}
