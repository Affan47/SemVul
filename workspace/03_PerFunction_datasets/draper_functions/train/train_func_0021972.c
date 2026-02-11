print_word(word *word, cell nesting)
{
	if(tagged<object>(word->vocabulary).type_p(STRING_TYPE))
		std::cout << untag<string>(word->vocabulary) << ":";

	if(tagged<object>(word->name).type_p(STRING_TYPE))
		std::cout << untag<string>(word->name);
	else
	{
		std::cout << "#<not a string: ";
		print_nested_obj(word->name,nesting);
		std::cout << ">";
	}
}
