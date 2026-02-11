f_srandom(int count, VALUE **vals)
{
	VALUE result;


	result.v_type = V_RANDOM;
	result.v_subtype = V_NOSUBTYPE;


	switch (count) {
	case 0:

		result.v_random = zsetrandom(NULL);
		break;

	case 1:
		switch (vals[0]->v_type) {
		case V_NUM:

			if (!qisint(vals[0]->v_num)) {
				math_error(
				  "srandom number seed must be an integer");

			}
			result.v_random = zsrandom1(vals[0]->v_num->num, TRUE);
			break;

		case V_RANDOM:

			result.v_random = zsetrandom(vals[0]->v_random);
			break;

		default:
			math_error("illegal type of arg passed to srandom()");

			break;
		}
		break;

	case 2:
		if (vals[0]->v_type != V_NUM || !qisint(vals[0]->v_num)) {
			math_error("srandom seed must be an integer");

		}
		if (vals[1]->v_type != V_NUM || !qisint(vals[1]->v_num)) {
			math_error("srandom Blum modulus must be an integer");

		}
		result.v_random = zsrandom2(vals[0]->v_num->num,
					    vals[1]->v_num->num);
		break;

	case 4:
		if (vals[0]->v_type != V_NUM || !qisint(vals[0]->v_num)) {
			math_error("srandom seed must be an integer");

		}
		if (vals[1]->v_type != V_NUM || !qisint(vals[1]->v_num)) {
			math_error("srandom 2nd arg must be an integer");

		}
		if (vals[2]->v_type != V_NUM || !qisint(vals[2]->v_num)) {
			math_error("srandom 3rd arg must be an integer");

		}
		if (vals[3]->v_type != V_NUM || !qisint(vals[3]->v_num)) {
			math_error("srandom 4th arg must be an integer");

		}
		if (zge24b(vals[3]->v_num->num)) {
			math_error("srandom trials count is excessive");

		}
		result.v_random = zsrandom4(vals[0]->v_num->num,
					    vals[1]->v_num->num,
					    vals[2]->v_num->num,
					    ztoi(vals[3]->v_num->num));
		break;

	default:
		math_error("bad arg count to srandom()");

		break;
	}


	return result;
}
