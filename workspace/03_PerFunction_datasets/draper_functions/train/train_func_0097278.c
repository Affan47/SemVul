showCookies()
{
    CookieDialog dialog(BrowserApplication::cookieJar(), this);
    dialog.exec();
}
