setup() {

    sigchld(0);


    screen = DefaultScreen(dis);
    root = RootWindow(dis,screen);


    sw = XDisplayWidth(dis,screen);
    sh = XDisplayHeight(dis,screen);


    win_focus = getcolor(FOCUS);
    win_unfocus = getcolor(UNFOCUS);


    grabkeys();


    mode = VIEW_VERTICAL_STACK;


    bool_quit = 0;


    head = NULL;
    current = NULL;


    master_size = sw*MASTER_SIZE;


    int i;
    for(i=0;i<TABLENGTH(desktops);++i) {
        desktops[i].master_size = master_size;
        desktops[i].mode = mode;
        desktops[i].head = head;
        desktops[i].current = current;
    }


    const Arg arg = {.i = 0};
    current_desktop = arg.i;
    change_desktop(arg);


    XSelectInput(dis,root,SubstructureNotifyMask|SubstructureRedirectMask);
}
