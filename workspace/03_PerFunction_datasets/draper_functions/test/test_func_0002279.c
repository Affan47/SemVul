makeXmpKey(const std::string& schemaNs,
                                      const std::string& propPath)
    {
        std::string property;
        std::string::size_type idx = propPath.find(':');
        if (idx == std::string::npos) {
            throw Exiv2::Error(44, propPath, schemaNs);
        }

        property = propPath.substr(idx + 1);
        std::string prefix = Exiv2::XmpProperties::prefix(schemaNs);
        if (prefix.empty()) {
            throw Exiv2::Error(36, propPath, schemaNs);
        }
        return Exiv2::XmpKey::AutoPtr(new Exiv2::XmpKey(prefix, property));
    }
