operator<(const ConstVector& y) const
{
	int i = std::min(length(), y.length());
	int ii = 0;
	while (ii < i && operator[](ii) == y[ii])
		ii++;
	if (ii < i)
		return operator[](ii) < y[ii];
	else
		return length() < y.length();
}
