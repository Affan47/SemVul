c_pmodm127(char UNUSED *name, int UNUSED count, VALUE **vals)
{
	VALUE result;
	ZVALUE q;
	ZVALUE temp;
	int i;


	result.v_type = V_NULL;
	if (vals[0]->v_type != V_NUM) {
		math_error("Non-numeric argument for pmodm127");

	}
	if (qisfrac(vals[0]->v_num)) {
		math_error("Non-integer argument for pmodm127");

	}
	if (qisneg(vals[0]->v_num) || qiszero(vals[0]->v_num)) {
		math_error("argument for pmodm127 <= 0");

	}


	q = vals[0]->v_num->num;


	if (havelastmod && zcmp(q, *lastmod)) {
		zfree(*lastmod);
		zfree(*lastmodinv);
		havelastmod = FALSE;
	}
	if (!havelastmod) {
		zcopy(q, lastmod);
		zbitvalue(2 * q.len * BASEB, &temp);
		zquo(temp, q, lastmodinv, 0);
		zfree(temp);
		havelastmod = TRUE;
	}


	result.v_num = qalloc();
	zcopy(p255, &result.v_num->num);
	result.v_type = V_NUM;


	for (i=8; i<127; ++i) {
#if 0

		(void) zmod(result.v_num->num, *lastmod, &temp, 0);
		zfree(result.v_num->num);
		result.v_num->num = temp;
#else
		zmod5_or_zmod(&result.v_num->num);
#endif
#if 0

		zmul(result.v_num->num, result.v_num->num, &temp);
#else
		zsquare(result.v_num->num, &temp);
#endif


		zfree(result.v_num->num);
		zshift(temp, 1, &result.v_num->num);
		zfree(temp);
	}
	zmod5_or_zmod(&result.v_num->num);


	return result;
}
