filenameConvert(const char* filename, const char* ext) {
    plString basename = plString(filename).beforeFirst('.');
    return basename + ext;
}
