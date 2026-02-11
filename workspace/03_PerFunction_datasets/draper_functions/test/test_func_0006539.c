setupWindow() {


    using namespace FbTk;
    typedef FbTk::Resource<vector<WinButton::Type> > WinButtonsResource;

    string titlebar_name[2];
    string titlebar_alt_name[2];
    titlebar_name[0] = screen().name() + ".titlebar.left";
    titlebar_alt_name[0] = screen().altName() + ".Titlebar.Left";
    titlebar_name[1] = screen().name() + ".titlebar.right";
    titlebar_alt_name[1] = screen().altName() + ".Titlebar.Right";

    WinButtonsResource *titlebar_side[2];


    ResourceManager &rm = screen().resourceManager();


    for (int i=0; i < 2; ++i) {
        titlebar_side[i] = dynamic_cast<WinButtonsResource *>(
                            rm.findResource( titlebar_name[i] ) );

        if (titlebar_side[i] != 0)
            continue;

        WinButton::Type titlebar_left[] =  {
            WinButton::STICK
        };

        WinButton::Type titlebar_right[] =  {
            WinButton::MINIMIZE,
            WinButton::MAXIMIZE,
            WinButton::CLOSE
        };

        WinButton::Type *begin = 0;
        WinButton::Type *end = 0;

        if (i == 0) {
            begin = titlebar_left;
            end = titlebar_left + 1;
        } else {
            begin = titlebar_right;
            end = titlebar_right + 3;
        }

        titlebar_side[i] =
            new WinButtonsResource(rm,
                                   WinButtonsResource::Type(begin, end),
                                   titlebar_name[i], titlebar_alt_name[i]);


        screen().addManagedResource(titlebar_side[i]);
    }

    updateButtons();


}
