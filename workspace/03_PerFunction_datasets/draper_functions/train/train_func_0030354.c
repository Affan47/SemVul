append0(std::string& str, unsigned int value, int width)
{
	poco_assert (width > 0 && width < 64);

	char buffer[64];
	std::sprintf(buffer, "%0*u", width, value);
	str.append(buffer);
}
