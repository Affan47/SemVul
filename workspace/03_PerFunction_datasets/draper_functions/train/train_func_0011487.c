cmsPluginTHR(cmsContext id, void* Plug_in)
{
    cmsPluginBase* Plugin;

    for (Plugin = (cmsPluginBase*) Plug_in;
         Plugin != NULL;
         Plugin = Plugin -> Next) {

            if (Plugin -> Magic != cmsPluginMagicNumber) {
                cmsSignalError(id, cmsERROR_UNKNOWN_EXTENSION, "Unrecognized plugin");
                return FALSE;
            }

            if (Plugin ->ExpectedVersion > LCMS_VERSION) {
                cmsSignalError(id, cmsERROR_UNKNOWN_EXTENSION, "plugin needs Little CMS %d, current version is %d",
                    Plugin ->ExpectedVersion, LCMS_VERSION);
                return FALSE;
            }

            switch (Plugin -> Type) {

                case cmsPluginMemHandlerSig:
                    if (!_cmsRegisterMemHandlerPlugin(id, Plugin)) return FALSE;
                    break;

                case cmsPluginInterpolationSig:
                    if (!_cmsRegisterInterpPlugin(id, Plugin)) return FALSE;
                    break;

                case cmsPluginTagTypeSig:
                    if (!_cmsRegisterTagTypePlugin(id, Plugin)) return FALSE;
                    break;

                case cmsPluginTagSig:
                    if (!_cmsRegisterTagPlugin(id, Plugin)) return FALSE;
                    break;

                case cmsPluginFormattersSig:
                    if (!_cmsRegisterFormattersPlugin(id, Plugin)) return FALSE;
                    break;

                case cmsPluginRenderingIntentSig:
                    if (!_cmsRegisterRenderingIntentPlugin(id, Plugin)) return FALSE;
                    break;

                case cmsPluginParametricCurveSig:
                    if (!_cmsRegisterParametricCurvesPlugin(id, Plugin)) return FALSE;
                    break;

                case cmsPluginMultiProcessElementSig:
                    if (!_cmsRegisterMultiProcessElementPlugin(id, Plugin)) return FALSE;
                    break;

                case cmsPluginOptimizationSig:
                    if (!_cmsRegisterOptimizationPlugin(id, Plugin)) return FALSE;
                    break;

                case cmsPluginTransformSig:
                    if (!_cmsRegisterTransformPlugin(id, Plugin)) return FALSE;
                    break;

                case cmsPluginMutexSig:
                    if (!_cmsRegisterMutexPlugin(id, Plugin)) return FALSE;
                    break;

                default:
                    cmsSignalError(id, cmsERROR_UNKNOWN_EXTENSION, "Unrecognized plugin type '%X'", Plugin -> Type);
                    return FALSE;
            }
    }


    return TRUE;
}
