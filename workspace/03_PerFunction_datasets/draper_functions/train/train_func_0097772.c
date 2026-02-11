init_rolling_window(std::list<std::string>& rolling_window, std::ifstream& memory_file) const
{
    std::string token;
    int count = 0;


    while (count < trigger && memory_file >> token) {
        logger << INFO << "Rolling window list: " << token << endl;
        rolling_window.push_back(token);
        count++;
    }

    return (count == trigger);
}
