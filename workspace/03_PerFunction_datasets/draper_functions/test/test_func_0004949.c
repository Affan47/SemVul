saveState( QSessionManager& )
    {
        KConfig* config = KApplication::kApplication()->sessionConfig();
        if ( KMainWindow::memberList().count() ){


            KMainWindow::memberList().first()->saveGlobalProperties(config);
        }

        int n = 0;
        foreach (KMainWindow* mw, KMainWindow::memberList()) {
            n++;
            mw->savePropertiesInternal(config, n);
        }

        KConfigGroup group( config, "Number" );
        group.writeEntry("NumberOfWindows", n );
        return true;
    }
