main(int ac, char **av)
{
    int			do_words = 1;
    int			do_docs = 1;
    int			alt_work_area = 0;
    String		configfile = DEFAULT_CONFIG_FILE;
    int			c;
    extern char		*optarg;

    while ((c = getopt(ac, av, "vdwc:a")) != -1)
    {
	switch (c)
	{
	    case 'c':
		configfile = optarg;
		break;
	    case 'v':
		verbose++;
		break;
	    case 'a':
		alt_work_area++;
		break;
	    case 'w':
	        do_words = 0;
	        break;
	    case 'd':
	        do_docs = 0;
	        break;
	    case '?':
		usage();
		break;
	}
    }

   HtConfiguration* config= HtConfiguration::config();
   config->Defaults(&defaults[0]);

    if (access((char*)configfile, R_OK) < 0)
    {
	reportError(form("Unable to find configuration file '%s'",
			 configfile.get()));
    }

   config->Read(configfile);


    String url_part_errors = HtURLCodec::instance()->ErrMsg();

    if (url_part_errors.length() != 0)
      reportError(form("Invalid url_part_aliases or common_url_parts: %s",
                       url_part_errors.get()));


    if (alt_work_area != 0)
    {
	String	configValue;

	configValue = config->Find("word_db");
	if (configValue.length() != 0)
	{
	    configValue << ".work";
	   config->Add("word_db", configValue);
	}

	configValue = config->Find("doc_db");
	if (configValue.length() != 0)
	{
	    configValue << ".work";
	   config->Add("doc_db", configValue);
	}

	configValue = config->Find("doc_index");
	if (configValue.length() != 0)
	{
	    configValue << ".work";
	   config->Add("doc_index", configValue);
	}

	configValue = config->Find("doc_excerpt");
	if (configValue.length() != 0)
	{
	    configValue << ".work";
	   config->Add("doc_excerpt", configValue);
	}
    }

    if (do_docs)
      {
	const String doc_list = config->Find("doc_list");
	DocumentDB docs;
	if (docs.Open(config->Find("doc_db"), config->Find("doc_index"),
		      config->Find("doc_excerpt")) == OK)
	  {
	    docs.LoadDB(doc_list, verbose);
	    docs.Close();
	  }
      }
    if (do_words)
      {


	WordContext::Initialize(*config);

	const String word_dump = config->Find("word_dump");
	HtWordList words(*config);
	if(words.Open(config->Find("word_db"), O_RDWR) == OK) {
	  words.Load(word_dump);
	  words.Close();
	}
      }

    return 0;
}
