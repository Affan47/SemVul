appendToString(Obj string, UInt len)
{
       UInt len1 = strlen(Value);
       GROW_STRING(string, len+len1+1);
       memcpy(CHARS_STRING(string) + len, (void *)Value, len1+1);
       SET_LEN_STRING(string, len+len1);
       return len + len1;
}
