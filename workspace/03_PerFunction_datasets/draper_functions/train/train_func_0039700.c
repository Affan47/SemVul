getContent(const string &line,
                       string &property,
                       string &value,
                       bool &isComment,
                       bool fuzzyComments)
{
    size_t start = 0;
    while (start < line.size() &&
           isspace(line[start])) {
        start++;
    }


    if (start == line.size()) {
        return false;
    }


    isComment = false;
    if (line[start] == '#') {
        if (!fuzzyComments) {
            return false;
        }
        isComment = true;
    }


    if (isComment) {
        start++;
        while (start < line.size() &&
               isspace(line[start])) {
            start++;
        }
    }


    size_t end = start;
    while (end < line.size() &&
           !isspace(line[end])) {
        end++;
    }
    property = line.substr(start, end - start);


    start = end;
    while (start < line.size() &&
           isspace(line[start])) {
        start++;
    }
    if (start == line.size() ||
        line[start] != '=') {

        return false;
    }


    start++;
    while (start < line.size() &&
           isspace(line[start])) {
        start++;
    }

    value = line.substr(start);


    size_t numspaces = 0;
    while (numspaces < value.size() &&
           isspace(value[value.size() - 1 - numspaces])) {
        numspaces++;
    }
    value.erase(value.size() - numspaces);


    return true;
}
