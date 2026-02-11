mode() const {
    if (end_hour == start_hour || (start_hour == 0 && end_hour == 24)) {
        return Always;
    } else if (start_hour == 24 && end_hour == 0) {
        return Never;
    }
    return Between;
}
