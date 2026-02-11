wiz_quantity_item(object_type *o_ptr, bool carried)
{
	int tmp_int;

	char tmp_val[3];


	if (artifact_p(o_ptr)) return;


	strnfmt(tmp_val, sizeof(tmp_val), "%d", o_ptr->number);


	if (get_string("Quantity: ", tmp_val, 3))
	{

		tmp_int = atoi(tmp_val);


		if (tmp_int < 1) tmp_int = 1;
		if (tmp_int > 99) tmp_int = 99;


		if (carried)
		{

			p_ptr->total_weight -= (o_ptr->number * o_ptr->weight);


			p_ptr->total_weight += (tmp_int * o_ptr->weight);
		}


		if (o_ptr->tval == TV_ROD)
		{
			o_ptr->pval = (o_ptr->pval / o_ptr->number) * tmp_int;
		}


		o_ptr->number = tmp_int;
	}
}
