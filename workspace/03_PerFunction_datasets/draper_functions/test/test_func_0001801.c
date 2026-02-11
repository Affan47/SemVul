ufobject_xml(UFObject *object, const char *indent)
    {
        std::string xml = object->XML(indent);
        return g_strdup(xml.c_str());
    }
