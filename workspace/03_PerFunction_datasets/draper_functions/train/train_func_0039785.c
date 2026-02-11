init_default_keybindings(void)
{
    char buf[MAX_BUF];
    int i;

    for(i=0;i< sizeof(def_keys)/sizeof(char *);i++) {
        strcpy(buf,def_keys[i]);
        parse_keybind_line(buf,i,1);
    }
}
