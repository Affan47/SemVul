printAttribute(const char *name, const UnicodeString value, int32_t )
{
    write_utf8_file(out, UnicodeString(" "));
    write_utf8_file(out, UnicodeString(name));
    write_utf8_file(out, UnicodeString(" = \""));
    write_utf8_file(out, value);
    write_utf8_file(out, UnicodeString("\""));
}
