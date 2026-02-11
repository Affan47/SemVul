FindPolyAreaFromApothem(float apothemlength, int number_of_sides, bool show_work)
{
	float area, base, angle, apothem;
	apothem = apothemlength;

	angle = static_cast<float>(360 / 2 ) / number_of_sides;
	if ( show_work == true)
	{
	  cout << "angle = (360 / 2) / " << number_of_sides << endl;
	  cout << "angle = " << 360 / 2 << " / " << number_of_sides << endl;
	  cout << "angle = " << static_cast<float>(360 / 2) / number_of_sides << endl << endl;
	}

	base = tan(degToRad(angle)) * apothem;
	if ( show_work == true)
	{
	  cout << "base = tan(" << angle << ") * " << apothem << endl;
	  cout << "base = " << tan(degToRad(angle)) << " * " << apothem << endl;
	  cout << "base = " << tan(degToRad(angle)) * apothem << endl << endl;
	}

	area = (base * apothem) * number_of_sides;
	if ( show_work == true)
	{
	  cout << "area = (" << base << " * " << apothem << ") * " << number_of_sides << endl;
	  cout << "area = " << base * apothem << " * " << number_of_sides << endl;
	  cout << "area = " << (base * apothem) * number_of_sides << endl << endl;
	}
	return area;
}
