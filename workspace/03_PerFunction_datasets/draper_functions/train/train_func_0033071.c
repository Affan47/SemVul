save(ostream & out, int indent, const XString& x_string) {
    Block b("SEGMENT", out, indent);
    get_region()->save(out, indent, x_string);
}
