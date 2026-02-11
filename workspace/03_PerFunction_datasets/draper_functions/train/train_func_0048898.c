callDebug( KJS::ExecState *exec, KJS::JSObject * , const KJS::List &args )
{

    qDebug()  << "Debug: " << toQString(args[0]->toString(exec));
    return KJS::jsNull();
}
