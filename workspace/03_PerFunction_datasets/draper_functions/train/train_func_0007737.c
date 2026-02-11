unantisubstitute_command(char *arg, struct session *ses)
{
    char left[BUFFER_SIZE];
    struct listnode *myantisubs, *ln, *temp;
    int flag;

    flag = FALSE;
    myantisubs = ses->antisubs;
    temp = myantisubs;
    arg = get_arg_in_braces(arg, left, 1);
    while ((ln = search_node_with_wild(temp, left)) != NULL)
    {
        if (ses->mesvar[2])
            tintin_printf(ses,"#Ok. Lines with {%s} will now be subbed.", ln->left);
        deletenode_list(myantisubs, ln);
        flag = TRUE;
    }
    if (!flag && ses->mesvar[2])
        tintin_printf(ses,"#THAT ANTISUBSTITUTE (%s) IS NOT DEFINED.", left);
}
