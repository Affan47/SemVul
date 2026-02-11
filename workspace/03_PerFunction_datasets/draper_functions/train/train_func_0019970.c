coord_string() {
    Inkscape::SVGOStringStream os;
    os << pt[0] << " : "
       << pt[1] << " : "
       << pt[2] << " : "
       << pt[3];
    return g_strdup(os.str().c_str());
}
