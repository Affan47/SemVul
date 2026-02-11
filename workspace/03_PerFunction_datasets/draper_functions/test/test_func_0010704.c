_ispell_provider_dictionary_exists (EnchantBroker * broker, const char *const szFile)
{
	std::vector <std::string> names;

	s_buildHashNames (names, broker, szFile);
	for (size_t i = 0; i < names.size(); i++) {
		if (g_file_test (names[i].c_str(), G_FILE_TEST_EXISTS))
			return 1;
	}

	return 0;
}
