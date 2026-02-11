toBool() const {
    if (compareTo("true", true) == 0)
        return true;
    if (compareTo("false", true) == 0)
        return false;
    return (toUint() != 0);
}
