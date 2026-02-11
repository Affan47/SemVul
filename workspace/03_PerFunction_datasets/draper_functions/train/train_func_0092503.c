GetString(const wxString &paramName)
{
   CheckParam(paramName);
   const wxVariant &v = mParams[paramName];
   TypeCheck(wxT("string"), paramName, v);
   return v.GetString();
}
