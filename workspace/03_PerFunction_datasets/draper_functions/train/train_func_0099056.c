handleTabPanePos (const EventArgs& e)
    {
        TabControl::TabPanePosition tpp;
        switch (static_cast<const WindowEventArgs&> (e).window->getID ())
        {
            case 0:
                tpp = TabControl::Top;
                break;
            case 1:
                tpp = TabControl::Bottom;
                break;
            default:
                return false;
        }


        WindowManager& winMgr = WindowManager::getSingleton ();
        if (winMgr.isWindowPresent("TabControlDemo/Frame/TabControl"))
        {
            static_cast<TabControl *>(winMgr.getWindow (
                "TabControlDemo/Frame/TabControl"))->setTabPanePosition (tpp);
        }

        return true;
    }
