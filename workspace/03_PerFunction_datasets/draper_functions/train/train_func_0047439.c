write_data(std::ostream& output, const std::string& file, const std::string& data)
{
    std::string variable_name = normalize_name(file);
    output << "// " << file << ": " << data.size() << " bytes\n";
    output << "unsigned char " << variable_name << "[] = \"";
    for (unsigned int i = 0; i < data.size(); i++)
    {
        if (i % 20 == 0)
        {
            output << "\"\n    \"";
        }
        output << to_hex_char(data[i]);

    }
    output << "\";\n";

    output << "unsigned int " << variable_name << "_size = " << data.size() << ";\n";
}
