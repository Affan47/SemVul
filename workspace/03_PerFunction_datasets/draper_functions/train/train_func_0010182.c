normalize()
{
    double len = length();
	if (len>0.0)
	{
		x /= len;
		y /= len;
		z /= len;
	}
	return(len);
}
