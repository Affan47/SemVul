createValNameList(GBDATA *gb_main,AW_window *aws, const char *awarName){
#if defined(DUMP)
    aw_message("ValidNameSelectionList was created");
#endif

    static struct selectValidNameStruct* svnp = new struct selectValidNameStruct;

    svnp->aws            = aws;
    svnp->gb_main        = gb_main;
    svnp->validNamesList = aws->create_selection_list(awarName,0,"",10,20);;
    svnp->initials       = "";

    fillSelNamList(svnp);
    return svnp;
}
