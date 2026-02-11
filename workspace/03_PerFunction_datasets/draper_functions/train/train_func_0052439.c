get_random_word_group () const
{
  std::string random_group;

  const int group_size = get_dictionary_group_size (dictionary_);
  random_group.resize (group_size);

  for (int group = 0; group < group_size; group++)
    {
      const char *element = get_dictionary_random_word (dictionary_);
      random_group += element;
    }

  return random_group;
}
