showFAQ()
{
    QDesktopServices::openUrl( "http://" + UnicornUtils::localizedHostName( The::settings().appLanguage() ) + "/help/faq/" );
}
