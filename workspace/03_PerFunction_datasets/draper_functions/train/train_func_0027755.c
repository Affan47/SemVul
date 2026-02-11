fileColour(const std::string& filename) {

    size_t slash = filename.rfind('/');
    size_t dot   = filename.rfind('.');

    if(dot != std::string::npos && dot+1<filename.size() && (slash == std::string::npos || slash < dot)) {
        std::string file_ext = filename.substr(dot+1);

        return colourHash(file_ext);
    } else {
        return vec3(1.0, 1.0, 1.0);
    }
}
