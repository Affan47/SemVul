lookup_state( pid_t pid ) {
    std::unordered_map<pid_t, pid_state>::iterator process=state.find(pid);

    if( process!=state.end() ) {
        return &process->second;
    }

    return NULL;
}
