run_dict_tests (enchant::Dict * dict)
{
	std::vector<std::string> suggs;
	size_t i, j;

	const char *check_checks[] = { "hello", "helllo" };
	const char *sugg_checks[] = { "helllo", "taag" };

	for (i = 0; i < (sizeof (check_checks) / sizeof (check_checks[0])); i++)
		{
			printf ("enchant_dict_check (%s): %d\n", check_checks[i],
				dict->check (check_checks[i]) == false);
		}

	for (i = 0; i < (sizeof (sugg_checks) / sizeof (sugg_checks[0])); i++)
		{
			dict->suggest (sugg_checks[i], suggs);

			printf ("enchant_dict_suggest(%s): %d\n", sugg_checks[i], suggs.size());
			for (j = 0; j < suggs.size(); j++)
				{
					printf ("\t=>%s\n", suggs[j].c_str());
				}
		}

	printf ("Adding 'helllo' to session\n");
	dict->add_to_session ("helllo");
	for (i = 0; i < (sizeof (check_checks) / sizeof (check_checks[0])); i++)
		{
			printf ("enchant_dict_check (%s): %d\n", check_checks[i],
				dict->check (check_checks[i]) == false);
		}

#if 0
	printf ("Adding 'helllo' to personal\n");
	dict->add_to_pwl ("helllo");
	for (i = 0; i < (sizeof (check_checks) / sizeof (check_checks[0])); i++)
		{
			printf ("enchant_dict_check (%s): %d\n", check_checks[i],
				dict->check (check_checks[i]) == false);
		}
#endif
}
