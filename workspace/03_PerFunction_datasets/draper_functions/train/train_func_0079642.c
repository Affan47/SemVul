rollup_write_data(uint idx, TABLE *table_arg)
{
  uint i;
  for (i= send_group_parts ; i-- > idx ; )
  {

    memcpy((char*) ref_pointer_array,
	   (char*) rollup.ref_pointer_arrays[i],
	   ref_pointer_array_size);
    if ((!having || having->val_int()))
    {
      int write_error;
      Item *item;
      List_iterator_fast<Item> it(rollup.fields[i]);
      while ((item= it++))
      {
        if (item->type() == Item::NULL_ITEM && item->is_result_field())
          item->save_in_result_field(1);
      }
      copy_sum_funcs(sum_funcs_end[i+1], sum_funcs_end[i]);
      if ((write_error= table_arg->file->ha_write_row(table_arg->record[0])))
      {
	if (create_myisam_from_heap(thd, table_arg, &tmp_table_param,
                                    write_error, 0))
	  return 1;
      }
    }
  }

  set_items_ref_array(current_ref_pointer_array);
  return 0;
}
