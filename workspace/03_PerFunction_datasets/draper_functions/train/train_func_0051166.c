interpolation(int inter)
{
	use_interpolation = inter;
	if(!csengine)
		return;

	csengine->filter = use_interpolation;
}
