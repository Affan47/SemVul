SetOriginal(const char* string) {
    delete _string;
    _string = strdup(string);
    uncacheExtent();
}
