format_network(guint64 rate, guint64 max_rate)
    {
        char* bytes = procman::format_size(rate, max_rate, ProcmanApp::get()->config.network_in_bits);
        std::string formatted(bytes);
        g_free(bytes);
        return formatted;
    }
