SetMode()
{
    QAction *act=qobject_cast<QAction *>(sender());

    if (act) {
        int data=act->data().toInt();

        if (0==data) {
            switch (mode_) {
            case Mode_LargeSidebar:         SetMode(Mode_IconOnlyLargeSidebar); break;
            case Mode_SmallSidebar:         SetMode(Mode_IconOnlySmallSidebar); break;
            case Mode_SideTabs:             SetMode(Mode_IconOnlySideTabs); break;
            case Mode_TopTabs:              SetMode(Mode_IconOnlyTopTabs); break;
            case Mode_IconOnlyTopTabs:      SetMode(Mode_TopTabs); break;
            case Mode_BotTabs:              SetMode(Mode_IconOnlyBotTabs); break;
            case Mode_IconOnlyBotTabs:      SetMode(Mode_BotTabs); break;
            case Mode_IconOnlyLargeSidebar: SetMode(Mode_LargeSidebar); break;
            case Mode_IconOnlySmallSidebar: SetMode(Mode_SmallSidebar); break;
            case Mode_IconOnlySideTabs:     SetMode(Mode_SideTabs); break;
            case Mode_BottomBar:            SetMode(Mode_IconOnlyBottomBar); break;
            case Mode_IconOnlyBottomBar:    SetMode(Mode_BottomBar); break;
            case Mode_TopBar:               SetMode(Mode_IconOnlyTopBar); break;
            case Mode_IconOnlyTopBar:       SetMode(Mode_TopBar); break;
            default: break;
            }
        } else {
            bool iconOnly=Mode_IconOnlyLargeSidebar==mode_ || Mode_IconOnlySmallSidebar==mode_ ||
                          Mode_IconOnlySideTabs==mode_ || Mode_IconOnlyTopTabs==mode_ ||
                          Mode_IconOnlyBotTabs==mode_ || Mode_IconOnlyBottomBar==mode_ ||
                          Mode_IconOnlyTopBar==mode_;
            switch (data) {
            case Mode_LargeSidebar: SetMode(iconOnly ? Mode_IconOnlyLargeSidebar : Mode_LargeSidebar); break;
            case Mode_SmallSidebar: SetMode(iconOnly ? Mode_IconOnlySmallSidebar : Mode_SmallSidebar); break;
            case Mode_SideTabs:     SetMode(iconOnly ? Mode_IconOnlySideTabs : Mode_SideTabs); break;
            case Mode_TopTabs:      SetMode(iconOnly ? Mode_IconOnlyTopTabs : Mode_TopTabs); break;
            case Mode_BotTabs:      SetMode(iconOnly ? Mode_IconOnlyBotTabs : Mode_BotTabs); break;
            case Mode_BottomBar:    SetMode(iconOnly ? Mode_IconOnlyBottomBar : Mode_BottomBar); break;
            case Mode_TopBar:       SetMode(iconOnly ? Mode_IconOnlyTopBar : Mode_TopBar); break;
            default: break;
            }
        }
    }
}
