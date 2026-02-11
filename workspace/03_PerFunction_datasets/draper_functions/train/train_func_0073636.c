callPrintLn( KJS::ExecState *exec, KJS::JSObject * , const KJS::List &args )
{
    (*KJSEmbed::conout()) << toQString(args[0]->toString(exec)) << endl;
    return KJS::jsNull();
}
