file_exists(const char* fn) {
    return fn && (access(fn, F_OK) == 0);
}
