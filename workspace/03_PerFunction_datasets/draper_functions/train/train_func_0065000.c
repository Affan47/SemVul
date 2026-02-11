EC_POINT_point2oct(const EC_GROUP *group, const EC_POINT *point, point_conversion_form_t form,
        unsigned char *buf, size_t len, BN_CTX *ctx)
	{
	if (group->meth->point2oct == 0
		&& !(group->meth->flags & EC_FLAGS_DEFAULT_OCT))
		{
		ECerr(EC_F_EC_POINT_POINT2OCT, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
		return 0;
		}
	if (group->meth != point->meth)
		{
		ECerr(EC_F_EC_POINT_POINT2OCT, EC_R_INCOMPATIBLE_OBJECTS);
		return 0;
		}
	if(group->meth->flags & EC_FLAGS_DEFAULT_OCT)
		{
		if (group->meth->field_type == NID_X9_62_prime_field)
			return ec_GFp_simple_point2oct(group, point,
							form, buf, len, ctx);
		else
#ifdef OPENSSL_NO_EC2M
			{
			ECerr(EC_F_EC_POINT_POINT2OCT, EC_R_GF2M_NOT_SUPPORTED);
			return 0;
			}
#else
			return ec_GF2m_simple_point2oct(group, point,
							form, buf, len, ctx);
#endif
		}

	return group->meth->point2oct(group, point, form, buf, len, ctx);
	}
