get_next_url() {
    if (!urls.size()) return NULL;
    while(1) {
        current_index = (current_index + 1)%((int)urls.size());
        if (current_index == start_index) {
            return NULL;
        }
        return urls[current_index].c_str();
    }
}
