type_path( a_Id_List path )
{
    static string str;


    str = "";

    while( path )
    {

        str += S_name(path->xid);

        if( path->next ) str += ".";

        path = path->next;
    }

    return str.c_str();
}
