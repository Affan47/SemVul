str_units(int n)
{
	if (n == 1)
		return display_in_cyl_units ? "cylinder" : "sector";
	return display_in_cyl_units ? "cylinders" : "sectors";
}
