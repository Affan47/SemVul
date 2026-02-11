setHomeToCurrentPage()
{
    BrowserMainWindow *mw = static_cast<BrowserMainWindow*>(parent());
    WebView *webView = mw->currentTab();
    if (webView)
        homeLineEdit->setText(QString::fromUtf8(webView->url().toEncoded()));
}
