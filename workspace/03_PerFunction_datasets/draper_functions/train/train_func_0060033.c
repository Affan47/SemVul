getObjResourceBool(const FWObject *obj,
				    const string&  resource_name)
{
    string res=getObjResourceStr(obj,resource_name);
    return (res=="true" || res=="True");
}
