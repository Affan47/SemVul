Defaults(const ConfigDefaults *array)
{
    for (int i = 0; array[i].name; i++)
    {
        AddParsed(array[i].name, array[i].value);
    }
}
