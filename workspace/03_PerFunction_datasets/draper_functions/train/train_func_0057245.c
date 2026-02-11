fribidi_char_set_name (

  FriBidiCharSet char_set
)
{
  return char_sets[char_set].name ? char_sets[char_set].name : "";
}
