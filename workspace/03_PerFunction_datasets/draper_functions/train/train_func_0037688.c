rTrim(string *str)
{
    string::reverse_iterator rit = str->rbegin();

     while(rit != str->rend() && isspace(*rit))
     {
         str->erase((++rit).base());
     }
}
