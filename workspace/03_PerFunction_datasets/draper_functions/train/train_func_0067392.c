findListener(const string &name)
{


    boost::uint8_t *addr = _baseaddr + LC_LISTENERS_START;
    char *item = reinterpret_cast<char *>(addr);

    while (*item != 0) {
        if (name == item) 	{
            return true;
        }
        item += strlen(item)+8+1;


    }

    return false;
}
