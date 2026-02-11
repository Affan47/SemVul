Size(const char* filename) {
    _socket = new SocketClient(host, port);
    std::string s = std::string("HEAD ") + filename + " HTTP/1.1\nHost: " + host;
    _socket->SendLine(std::string("HEAD ") + filename + " HTTP/1.1\r");
    _socket->SendLine(std::string("Host: ") + host + "\r");
    _socket->SendLine(std::string("\r"));


    std::string prefix = "content-length:";
    s = _socket->ReceiveLine();
    long long result = -1;
    while (s != "") {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        if (s.substr(0, prefix.size()) == prefix) {
            if (1 != sscanf(s.c_str() + prefix.size() + 1, "%lld", &result))
                throw "UNSUPPORTED_RESPONSE";
            break;
        }
        s = _socket->ReceiveLine();
    }
    _socket->Close();
    delete _socket;
    _socket = 0;
    return result;
}
