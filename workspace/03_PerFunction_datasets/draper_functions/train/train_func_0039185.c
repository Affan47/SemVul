truncate2 (const cl_SF& x, const cl_SF& y)
{


	var cl_SF_div_t q_r = truncate2(x/y);
	var cl_I& q = q_r.quotient;
	var cl_SF& r = q_r.remainder;
	return cl_SF_div_t(q,y*r);
}

}
