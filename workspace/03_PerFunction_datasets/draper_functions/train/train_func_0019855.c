get_border_width(pdf_obj *obj)
{
	float w = pdf_to_real(pdf_dict_getp(obj, "BS/W"));
	return w == 0.0 ? 1.0 : w;
}
