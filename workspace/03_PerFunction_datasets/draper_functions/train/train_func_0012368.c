Report()
{
	AString temp;
	temp += ItemString(item, amount) + " at $" + price;
	return temp;
}
