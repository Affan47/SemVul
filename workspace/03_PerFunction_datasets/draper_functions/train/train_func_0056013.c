add_import(const char *s)
{ if (find_if(imports.begin(), imports.end(), eqstr(s)) == imports.end())
    imports.push_back(s);
}
