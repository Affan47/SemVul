getView(OpenUrlIn tab, WebView *currentView)
{
    WebView *webView = 0;
    switch (tab) {
        case NewWindow: {
#ifdef USERMODIFIEDBEHAVIOR_DEBUG
            qDebug() << __FUNCTION__ << "NewWindow";
#endif
            BrowserMainWindow *newMainWindow = BrowserApplication::instance()->newMainWindow();
            webView = newMainWindow->currentTab();
            webView->setFocus();
            break;
        }

        case NewSelectedTab: {
#ifdef USERMODIFIEDBEHAVIOR_DEBUG
            qDebug() << __FUNCTION__ << "NewSelectedTab";
#endif
            webView = makeNewTab(true);
            webView->setFocus();
            break;
        }

        case NewNotSelectedTab: {
#ifdef USERMODIFIEDBEHAVIOR_DEBUG
            qDebug() << __FUNCTION__ << "NewNotSelectedTab";
#endif
            webView = makeNewTab(false);
            break;
        }

        case CurrentTab:
        default:
#ifdef USERMODIFIEDBEHAVIOR_DEBUG
            qDebug() << __FUNCTION__ << "CurrentTab";
#endif
            webView = currentView;
            if (!webView)
                return 0;
            webView->setFocus();
            break;
    }
    return webView;
}
