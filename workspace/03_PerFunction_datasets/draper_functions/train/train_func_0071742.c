CreateFromEnv()
    {
        char* file = std::getenv(OCIO_CONFIG_ENVVAR);
        if(file) return CreateFromFile(file);

        std::ostringstream os;
        os << "Color management disabled. ";
        os << "(Specify the $OCIO environment variable to enable.)";
        LogInfo(os.str());

        std::istringstream istream;
        istream.str(INTERNAL_RAW_PROFILE);

        ConfigRcPtr config = Config::Create();
        config->getImpl()->io_.open(istream, config);
        return config;
    }
