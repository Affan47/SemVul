substitute(UString &string, const UString &substring)
{
    int position = string.find("%s");
    assert(position != -1);
    UString newString = string.substr(0, position);
    newString.append(substring);
    newString.append(string.substr(position + 2));
    string = newString;
}
