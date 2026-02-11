string_to_vector(const std::string& str)
{
    const char SEPARATOR = '.';

    std::vector<std::string> result;

    size_t length = str.size();
    size_t i = 0;
    std::string acc;
    while (i < length) {
	if (str[i] == SEPARATOR) {
	    result.push_back(acc);
	    acc.clear();
	} else {
	    acc += str[i];
	}
	i++;
    }
    if (!acc.empty()) {
	result.push_back(acc);
    }

    return result;
}
