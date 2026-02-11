rd_artifacts(void)
{
	int i;
	u16b tmp16u;


	rd_u16b(&tmp16u);


	if (tmp16u > z_info->a_max)
	{
		note(format("Too many (%u) artifacts!", tmp16u));
		return (-1);
	}


	for (i = 0; i < tmp16u; i++)
	{
		byte tmp8u;

		rd_byte(&tmp8u);
		a_info[i].created = tmp8u;
		rd_byte(&tmp8u);
		rd_byte(&tmp8u);
		rd_byte(&tmp8u);
	}


	{
		size_t i;
		object_type *o_ptr = NULL;

		bool *anywhere;
		anywhere = C_ZNEW(z_info->a_max, bool);


		for (i = 0; i < INVEN_TOTAL; i++)
		{
			o_ptr = &o_list[i];
			if (object_is_known_artifact(o_ptr))
				artifact_of(o_ptr)->seen = TRUE;
			anywhere[o_ptr->name1] = TRUE;
		}

		for (i = 0; i < (size_t)o_max; i++)
		{
			o_ptr = &o_list[i];
			if (object_is_known_artifact(o_ptr))
				artifact_of(o_ptr)->seen = TRUE;
			anywhere[o_ptr->name1] = TRUE;
		}

		for (i = 0; i < MAX_STORES; i++)
		{
			int j = 0;
			for (j = 0; j < store[i].stock_num; j++)
			{
				o_ptr = &store[i].stock[j];
				if (object_is_known_artifact(o_ptr))
					artifact_of(o_ptr)->seen = TRUE;
				anywhere[o_ptr->name1] = TRUE;
			}
		}


		for (i = 0; i < z_info->a_max; i++)
		{
			artifact_type *a_ptr = &a_info[i];


			if (a_ptr->created && !anywhere[i])
				a_ptr->seen = TRUE;
		}

		FREE(anywhere);
	}


	return 0;
}
