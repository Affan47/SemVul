rewind()
{


  if (!is_empty())
  {
    for (uint i=  0; i < array.elements; i++)
    {
      Log_event *ev= *(Log_event **) dynamic_array_ptr(&array, i);
      delete ev;
    }
    last_added= NULL;
    if (array.elements > array.max_element)
      freeze_size(&array);
    reset_dynamic(&array);
    last_added= NULL;
  }
}
