initialize() {
    if (parserDelegate == NULL) {
        return;
    }
    std::vector<Value> args;
    aikido->call (parserDelegate, "initialize", args);
}
