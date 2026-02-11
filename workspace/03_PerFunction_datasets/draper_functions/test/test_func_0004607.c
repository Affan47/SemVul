any_process_exists(vector<int>& pids) {
    int status;
    for (unsigned int i=0; i<pids.size(); i++) {
        if (waitpid(pids[i], &status, WNOHANG) >= 0) {
            return true;
        }
    }
    return false;
}
