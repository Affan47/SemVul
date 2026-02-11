pack() {
    if (empty())
        return *this;
    return operator=(plString(fString->data()));
}
