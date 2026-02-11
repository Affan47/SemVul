setParseMode(KEmoticonsTheme::ParseMode mode)
{
    KConfigGroup config(KSharedConfig::openConfig("kdeglobals"), "Emoticons");
    config.writeEntry("parseMode", int(mode));
    config.sync();
}
