DumpStructureToFile(const char *fn)
{
    std::ofstream f;
    f.open(fn);
    if(!f.is_open())
        return;

    uint32 *ftype = new uint32[_fields_per_row];
    ftype[0] = SCP_TYPE_INT;

    f << "Fields: (0 is always index field)\n";
    for(std::map<std::string,SCPFieldDef>::iterator it = _fielddefs.begin(); it != _fielddefs.end(); it++)
    {
        f << "-> Name: " << it->first << ", ID: " << it->second.id << ", type: " << gettypename(it->second.type) << "\n";
        ftype[it->second.id] = it->second.type;
    }
    f << "\n";

    for(uint32 row = 0; row < _rowcount; row++)
    {
        for(uint32 column = 0; column < _fields_per_row; column++)
        {
            if(ftype[column] == SCP_TYPE_INT)
                f << *((int*)&_intbuf[row * _fields_per_row + column]) << "\t";
            else if(ftype[column] == SCP_TYPE_FLOAT)
                f << *((float*)&_intbuf[row * _fields_per_row + column]) << "\t";
            else
                f << "S_" << _intbuf[row * _fields_per_row + column] << "\t";
        }
        f << "\n";
    }

    f << "\nStrings:\n";
    for(uint32 i = 0; i < _stringsize; i++)
    {
        if(!_stringbuf[i])
        {
            i++;
            if(i >= _stringsize)
                break;
            f << "\n" << i << ": ";
        }
        f << _stringbuf[i];
    }
}
