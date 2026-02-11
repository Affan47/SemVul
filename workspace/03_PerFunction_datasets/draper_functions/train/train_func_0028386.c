CountAttrList(IMListOfAttr *attr, int *total_count)
{
    *total_count = 0;

    while (attr->name != NULL)
    {
        attr++;
        ++(*total_count);
    }
}
