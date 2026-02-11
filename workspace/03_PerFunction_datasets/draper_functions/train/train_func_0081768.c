get_formatting_used_has_translatable_choices() const
{
  const Formatting& formatting = get_formatting_used();
  if(!formatting.get_has_custom_choices())
    return false;

  bool as_radio_buttons = false;
  if(!formatting.get_choices_restricted(as_radio_buttons))
    return false;

  return true;
}
