f_digits(int count, VALUE **vals)
{
	ZVALUE base;
	VALUE res;

	if (vals[0]->v_type != V_NUM)
		return error_value(E_DGTS1);
	if (count > 1) {
		if (vals[1]->v_type != V_NUM || qisfrac(vals[1]->v_num)
			|| qiszero(vals[1]->v_num) || qisunit(vals[1]->v_num))
			return error_value(E_DGTS2);
		base = vals[1]->v_num->num;
	} else {
		base = _ten_;
	}
	res.v_type = V_NUM;
	res.v_num = itoq(qdigits(vals[0]->v_num, base));
	return res;
}
