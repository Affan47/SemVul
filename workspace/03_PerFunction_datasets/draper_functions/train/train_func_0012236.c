divide() {
    double result = std::numeric_limits<double>::quiet_NaN();
    for(std::list<double>::const_iterator i = values.begin(); i != values.end(); ++i) {
        if (i == values.begin()) {
            result = *i;
        } else {
            result /= *i;
        }
    }
    return result;
}
