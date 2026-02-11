isDisjoint() const
{
	return
		matrix[Location::INTERIOR][Location::INTERIOR]==Dimension::False
		&&
		matrix[Location::INTERIOR][Location::BOUNDARY]==Dimension::False
		&&
		matrix[Location::BOUNDARY][Location::INTERIOR]==Dimension::False
		&&
		matrix[Location::BOUNDARY][Location::BOUNDARY]==Dimension::False;
}
