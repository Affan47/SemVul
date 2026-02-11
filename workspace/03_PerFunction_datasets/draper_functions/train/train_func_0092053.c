mark_fields_used(trg_event_type event)
{
  int action_time;
  Item_trigger_field *trg_field;

  for (action_time= 0; action_time < (int)TRG_ACTION_MAX; action_time++)
  {
    for (trg_field= trigger_fields[event][action_time]; trg_field;
         trg_field= trg_field->next_trg_field)
    {

      if (trg_field->field_idx != (uint)-1)
      {
        bitmap_set_bit(trigger_table->read_set, trg_field->field_idx);
        if (trg_field->get_settable_routine_parameter())
          bitmap_set_bit(trigger_table->write_set, trg_field->field_idx);
      }
    }
  }
  trigger_table->file->column_bitmaps_signal();
}
