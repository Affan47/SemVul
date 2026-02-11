init(std::string dir, std::string log_file) {
    if (!dir.empty()) {
        int ret = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (ret != 0 && errno != EEXIST) {
            printf("mkdir error which dir:%s err:%s\n", dir.c_str(), strerror(errno));
            _is_inited = true;
            return -1;
        }
    } else {
        dir = ".";
    }
    _log_dir = dir;
    _log_file = log_file;
    _log_file_path = dir + "/" + log_file;
    _fs.open(_log_file_path.c_str(), std::fstream::out | std::fstream::app);
    _is_inited = true;
    pthread_mutex_init(&writelock, NULL);
    return 0;
}
