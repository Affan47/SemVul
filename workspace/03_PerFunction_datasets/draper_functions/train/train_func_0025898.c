borg_load_requirement(char * string)
{
    int class_num=-1;
    int depth_num=-1;
    int item_num=-1;
    int number_items=-1;
    int x=-1;

    if (-1000 == (class_num = borg_getval(&string, "_CLASS")))
    {
        borg_note("Malformed item requirment in borg.txt");
        return FALSE;
    }
    if (-1000 == (depth_num = borg_getval(&string, "_DEPTH")))
    {
        borg_note("Malformed item requirment in borg.txt");
        return FALSE;
    }
    if (-1000 != (item_num = borg_getval(&string, "_FORMULA")))
    {
        return add_required_item(class_num, depth_num, -1, item_num);
    }
    if (-1000 != (item_num = borg_getval(&string, "_ITEM")))
    {
        string++;
        sscanf(string, "%d", &number_items);
        return add_required_item(class_num, depth_num, item_num, number_items);
    }
    if (-1000 != (item_num = borg_getval(&string, "_WITEM")))
    {
        string++;
        sscanf(string, "%d", &number_items);
        return add_required_item(class_num, depth_num,  z_info->k_max + item_num, number_items);
    }
    if (-1000 != (item_num = borg_getval(&string, "_ARTIFACT")))
    {
        string++;
        sscanf(string, "%d", &number_items);
        return add_required_item(class_num, depth_num, z_info->k_max + z_info->k_max +item_num, number_items);
    }

    for (x = 0; x < BI_MAX; x++)
    {

        if (prefix(string, prefix_pref[x]))
        {
            string += strlen(prefix_pref[x]);
            item_num = z_info->k_max + z_info->k_max + z_info->a_max + x;
            string++;
            sscanf(string, "%d", &number_items);
            return add_required_item(class_num, depth_num, item_num, number_items);
        }
    }
    borg_note("Malformed item requirment in borg.txt");
    return FALSE;
}
