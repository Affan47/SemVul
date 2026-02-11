_resolve(const std::string& filename, const std::string& cwd) {
    if (filename.size() >= 1) {
        if (isSlash(filename[0])) {

            return filename;
        } else {

            #ifdef G3D_WIN32
                if ((filename.size() >= 2) && (filename[1] == ':')) {

                    if ((filename.size() >= 3) && isSlash(filename[2])) {

                        return filename;
                    } else {


                        debugAssertM(false, "Files of the form d:path are"
                                     " not supported (use a fully qualified"
                                     " name).");
                        return filename;
                    }
                }
            #endif
        }
    }


    return FilePath::concat(cwd, filename);
}
