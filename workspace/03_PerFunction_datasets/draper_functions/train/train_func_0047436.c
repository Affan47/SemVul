revConvert(char i)
{
    if(i<0)
    {
        string s;
        s = "An error occured while doing revert conversion. ";
        s += "Function: revConvert, array: revConversion, index: ";
        s += "less than 0.";
        throw new IndexOutOfRangeException(s.c_str());
    }
    return revConversion[i];
}
