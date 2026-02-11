poppler_form_field_choice_commit_on_change (PopplerFormField *field)
{
  g_return_val_if_fail (field->widget->getType () == formChoice, FALSE);

  return static_cast<FormWidgetChoice*>(field->widget)->commitOnSelChange ();
}
