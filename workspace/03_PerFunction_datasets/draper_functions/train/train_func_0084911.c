memberof_copy_config(MemberOfConfig *dest, MemberOfConfig *src)
{
	if (dest && src)
	{

		if (src->groupattrs)
		{
			int i = 0, j = 0;


			slapi_ch_array_free(dest->groupattrs);
			dest->groupattrs = slapi_ch_array_dup(src->groupattrs);


			slapi_filter_free(dest->group_filter, 1);
			dest->group_filter = slapi_filter_dup(src->group_filter);


			for (i = 0; dest->group_slapiattrs && dest->group_slapiattrs[i]; i++)
			{
				slapi_attr_free(&dest->group_slapiattrs[i]);
			}


			for (j = 0; src->group_slapiattrs[j]; j++)
			{

			}


			if (i < j)
			{
				dest->group_slapiattrs = (Slapi_Attr **)slapi_ch_realloc((char *)dest->group_slapiattrs, sizeof(Slapi_Attr *) * (j + 1));
			}


			for (i = 0; src->group_slapiattrs[i]; i++)
			{
				dest->group_slapiattrs[i] = slapi_attr_dup(src->group_slapiattrs[i]);
			}


			dest->group_slapiattrs[i] = NULL;
		}

		if (src->memberof_attr)
		{
			slapi_ch_free_string(&dest->memberof_attr);
			dest->memberof_attr = slapi_ch_strdup(src->memberof_attr);
		}

		if(src->allBackends)
		{
			dest->allBackends = src->allBackends;
		}
	}
}
