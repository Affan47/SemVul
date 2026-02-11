callValueType( KJS::ExecState *exec, KJS::JSObject *self, const KJS::List &args )
{
    Q_UNUSED(args);
    KJSEmbed::ValueBinding *imp = KJSEmbed::extractBindingImp<KJSEmbed::ValueBinding>(exec,  self );
    if( imp )
    {
        return KJS::jsString( imp->className().ascii() );
    }
    return KJS::jsNull();
}
