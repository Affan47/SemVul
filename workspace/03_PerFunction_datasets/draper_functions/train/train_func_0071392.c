main(int argc, char *argv[])
{
    if (!TXT_Init())
    {
        fprintf(stderr, "Failed to initialise GUI\n");
        exit(-1);
    }

    TXT_SetDesktopTitle("Not Chocolate Doom Setup");

    ScrollingMenu();
    Window2();
    SetupWindow();

    TXT_GUIMainLoop();

    TXT_Shutdown();

    return 0;
}
