dohelp(void)
{
    int sel = 0;

    if (help_menu(&sel))
    {
        switch (sel)
        {
        case  0:  display_file(HELP, true);  break;
        case  1:  display_file(SHELP, true);  break;
        case  2:  dohistory();  break;
        case  3:  dowhatis();  break;
        case  4:  dowhatdoes();  break;
        case  5:  option_help();  break;
        case  6:  display_file(OPTIONFILE, true);  break;
        case  7:  doextlist();  break;
        case  8:  display_file(LICENSE, true);  break;
#ifdef WIZARD

        default: display_file(DEBUGHELP, true);  break;
#endif
#ifdef PORT_HELP
        case PORT_HELP_ID:  port_help();  break;
#endif
        }
    }
    return 0;
}
