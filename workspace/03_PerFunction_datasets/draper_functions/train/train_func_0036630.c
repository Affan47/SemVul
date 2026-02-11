get_category_data (int version,
		   guint8 const **category_data,
		   guint16 const **category_astral_index)
{
	*category_astral_index = NULL;

#ifndef DISABLE_NET_4_0
	if (version == 4) {
		*category_data = CategoryData_v4;
#ifndef DISABLE_ASTRAL
		*category_astral_index = CategoryData_v4_astral_index;
#endif
		return;
	}
#endif

	*category_data = CategoryData_v2;
#ifndef DISABLE_ASTRAL
	*category_astral_index = CategoryData_v2_astral_index;
#endif
}
