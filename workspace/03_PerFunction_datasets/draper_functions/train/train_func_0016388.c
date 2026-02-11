write_export_line(std::ostream& os) const {

    for (unsigned i(0); i<SIZE; ++i) {
        if (_entry[i]==0) break;
        if (i) os << '\t';
        os << _entry[i];
    }
}
