systemLanguage(as_object& proto)
{


	std::string lang = getVM(proto).getSystemLanguage();

	const char* languages[] = {"en", "fr", "ko", "ja", "sv",
				"de", "es", "it", "zh", "pt",
				"pl", "hu", "cs", "tr", "fi",
				"da", "nl", "no", "ru"};

	const size_t size = arraySize(languages);

	if (std::find(languages, languages + size, lang.substr(0, 2)) !=
            languages + size) {
		if (lang.substr(0, 2) == "zh") {


			if (lang.substr(2, 3) == "_TW") lang = "zh-TW";
			else if (lang.substr(2, 3) == "_CN") lang = "zh-CN";
			else lang = "xu";
		}
		else {


			lang.erase(2);
		}
	}
	else {


		lang = "xu";
	}

	return lang;
}

}
