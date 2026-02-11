set_sliding_window_size(const std::string& str)
{
    if(!str.empty()) {
        SLIDING_WINDOW_SIZE = atoi(str.c_str());
    } else {
	SLIDING_WINDOW_SIZE = DEFAULT_SLIDING_WINDOW_SIZE;
    }
}
