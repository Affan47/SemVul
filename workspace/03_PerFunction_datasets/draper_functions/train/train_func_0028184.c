finditem_command(char *arg,struct session *ses)
{
    char left[BUFFER_SIZE], list[BUFFER_SIZE], item[BUFFER_SIZE];

    arg = get_arg(arg, left,0,ses);
    arg = get_arg(arg, item,0,ses);
    arg = get_arg(arg, list,1,ses);
    if (!*left)
        tintin_eprintf(ses,"#Error - Syntax: #finditem {dest var} {item} {list}");
    else
    {
        sprintf(item,"%d",find_item(item,list));
        set_variable(left,item,ses);
    }
}
