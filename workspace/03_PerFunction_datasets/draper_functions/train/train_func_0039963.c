IfForceUnregister(PILInterface *id)
{
	if (DEBUGPLUGIN) {
		PILLog(PIL_DEBUG, "IfForceUnRegister(%s)"
		,	id->interfacename);
	}
	RemoveAPILInterface(id);
}
