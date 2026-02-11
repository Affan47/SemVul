InitLogging()
        {
            if(g_initialized) return;

            g_initialized = true;

            char* levelstr = std::getenv(OCIO_LOGGING_LEVEL_ENVVAR);
            if(levelstr)
            {
                g_loggingOverride = true;
                g_logginglevel = LoggingLevelFromString(levelstr);

                if(g_logginglevel == LOGGING_LEVEL_UNKNOWN)
                {
                    std::cerr << "[OpenColorIO Warning]: Invalid $OCIO_LOGGING_LEVEL specified. ";
                    std::cerr << "Options: none (0), warning (1), info (2), debug (3)" << std::endl;
                    g_logginglevel = OCIO_DEFAULT_LOGGING_LEVEL;
                }
            }
            else
            {
                g_logginglevel = OCIO_DEFAULT_LOGGING_LEVEL;
            }
        }
