Copy() const
{
    List	*list = new List;
    ListCursor  cursor;

    Start_Get(cursor);
    Object	*obj;
    while ((obj = Get_Next(cursor)))
    {
	list->Add(obj->Copy());
    }
    return list;
}
