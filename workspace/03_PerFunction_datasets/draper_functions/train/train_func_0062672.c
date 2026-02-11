PluginGetValue(NPPVariable variable, void *value)
{
    NPError err = NPERR_NO_ERROR;


    if (variable == NPPVpluginNameString) {
        *((const char **) value) = "QuickTime Plug-in 7.6.9";
    }
    if (variable == NPPVpluginDescriptionString) {
        *((const char **) value) =
            "<a href=\"http://kdekorte.googlepages.com/gecko-mediaplayer\">Gecko Media Player</a> "
            VERSION
            "<br><br>Video Player Plug-in for QuickTime, RealPlayer and Windows Media Player streams using <a href=\"http://mplayerhq.hu\">MPlayer</a>";

    }

    if (variable == NPPVpluginNeedsXEmbed) {
        *((bool *) value) = TRUE;
    }

    if ((variable != NPPVpluginNameString)
        && (variable != NPPVpluginDescriptionString)
        && (variable != NPPVpluginNeedsXEmbed)) {
        err = NPERR_INVALID_PARAM;
    }

    return err;


}
