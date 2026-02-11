string_rest_of_args (dollar_star)
     int dollar_star;
{
  register WORD_LIST *list;
  char *string;

  list = list_rest_of_args ();
  string = dollar_star ? string_list_dollar_star (list) : string_list (list);
  dispose_words (list);
  return (string);
}
