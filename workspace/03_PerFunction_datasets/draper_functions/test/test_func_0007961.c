hr_class(HOST& host, int hr_type) {
    switch (hr_type) {
    case 1:
        return os(host) + cpu_fine(host);
    case 2:
        switch (os(host)) {
        case Windows:
        case Linux:
            return os(host);
        case Darwin:
            return os(host) + cpu_coarse(host);
        }
    }
    return 0;
}
