toggle_update_cb (GtkWidget *widget, GapArrArg *arr_ptr)
{
  if(arr_ptr->widget_type !=GAP_ARR_WGT_TOGGLE) return;

  if (GTK_TOGGLE_BUTTON (widget)->active)
  {
    arr_ptr->int_ret = 1;
  }
  else
  {
    arr_ptr->int_ret = 0;
  }
}
