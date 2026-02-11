NPP_New(NPMIMEType pluginType,
    NPP instance,
    uint16 mode,
    int16 argc,
    char* argn[],
    char* argv[],
    NPSavedData* )
{
    if (!instance)
	return NPERR_INVALID_INSTANCE_ERROR;

    QtNPInstance* This = new QtNPInstance;
    if (!This)
	return NPERR_OUT_OF_MEMORY_ERROR;

    instance->pdata = This;
    This->filter = 0;
    This->bindable = 0;
    This->npp = instance;
    This->fMode = mode;
    This->window = 0;
    This->qt.object = 0;
#ifdef Q_WS_MAC
    This->rootWidget = 0;
#endif
    This->pendingStream = 0;
    This->mimetype = QString::fromLatin1(pluginType);
    This->notificationSeqNum = 0;

    for (int i = 0; i < argc; i++) {
        QByteArray name = QByteArray(argn[i]).toLower();
        if (name == "id")
            This->htmlID = argv[i];
        This->parameters[name] = QVariant(argv[i]);
    }

    return NPERR_NO_ERROR;
}
