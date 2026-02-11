free_item_data(gpointer data, GClosure * closure)
{


  if (data_ptr->data != NULL)
  {
    if (data_ptr->data_free != NULL)
    {
      data_ptr->data_free(data_ptr->data);
    }
    else
    {
      free(data_ptr->data);
    }
  }

  free(data_ptr);
}
