removeAsm(std::string &str)
{
    std::string::size_type pos = 0;
    while ((pos = str.find("\nasm(", pos)) != std::string::npos)
    {
        _removeAsm(str, pos++);
        str.insert(pos, "asm()");
    }

    pos = 0;
    while ((pos = str.find("\nasm (", pos)) != std::string::npos)
    {
        _removeAsm(str, pos++);
        str.insert(pos, "asm()");
    }

    pos = 0;
    while ((pos = str.find("\nasm __volatile(", pos)) != std::string::npos)
        _removeAsm(str, pos);

    pos = 0;
    while ((pos = str.find("\nasm __volatile (", pos)) != std::string::npos)
        _removeAsm(str, pos);
}
