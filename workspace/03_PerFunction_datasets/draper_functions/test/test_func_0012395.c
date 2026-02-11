inMemFunc(const char* func_name) const
{
   H5std_string full_name = func_name;
   full_name.insert(0, "::");
   full_name.insert(0, fromClass());
   return (full_name);
}
