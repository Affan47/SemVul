fill(units the_units, bool closepath)
{
	stroke_or_fill('f', the_units, -1.0, closepath);
	bounding_box_update(bounding_box(the_units));
}
