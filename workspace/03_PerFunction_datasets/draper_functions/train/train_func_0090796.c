fribidi_char_set_title (

  FriBidiCharSet char_set
)
{
  return char_sets[char_set].title ? char_sets[char_set].
    title : fribidi_char_set_name (char_set);
}
