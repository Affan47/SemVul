f_places(int count, VALUE **vals)
{
	long places;
	VALUE res;

	if (vals[0]->v_type != V_NUM)
		return error_value(E_PLCS1);
	if (count > 1) {
		if (vals[1]->v_type != V_NUM || qisfrac(vals[1]->v_num))
			return error_value(E_PLCS2);
		places = qplaces(vals[0]->v_num, vals[1]->v_num->num);
		if (places == -2)
			return error_value(E_PLCS2);
	} else
		places = qdecplaces(vals[0]->v_num);

	res.v_type = V_NUM;
	res.v_num = itoq(places);
	return res;
}
