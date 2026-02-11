execStateForPrincipal(ScriptableExtension* caller)
{
    KHTMLPart* part = partForPrincipal(caller);

    if (!part)
        return 0;

    KJSProxy* proxy = KJSProxy::proxy(part);
    if (!proxy)
        return 0;

    KJS::Interpreter* i = proxy->interpreter();
    if (!i)
        return 0;

    return i->globalExec();
}
