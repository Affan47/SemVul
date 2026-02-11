getNextLine(std::string& line) {


    if(isFinished()) stream->clear();

#ifdef _WIN32

    DWORD available_bytes;

    if (!PeekNamedPipe(stdin_handle, 0, 0, 0,
        &available_bytes, 0)) return false;

    if(available_bytes==0) return false;

#endif

    std::getline(*stream, line);


    if (line.size() > 0 && line[line.size()-1] == '\r') {
        line.resize(line.size() - 1);
    }

    if(isFinished()) {
        return false;
    }

    return true;
}
