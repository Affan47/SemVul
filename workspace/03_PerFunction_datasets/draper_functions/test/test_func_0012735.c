global(localization_backend_manager const &in)
        {
            boost::unique_lock<boost::mutex> lock(localization_backend_manager_mutex());
            localization_backend_manager mgr = localization_backend_manager_global();
            localization_backend_manager_global() = in;
            return mgr;
        }
