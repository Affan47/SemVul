beginObject(const std::string& name, const std::string& type)
{
    log_trace("beginObject(\"" << name << "\", \"" << type << ')');
    *_out << static_cast<char>(Serializer::CategoryObject)
          << name << '\0';
    printTypeCode(*_out, type, false);
}
