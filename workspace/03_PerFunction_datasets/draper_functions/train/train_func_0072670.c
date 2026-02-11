registerNamedObject(const ObjectSignature &sig,
                                      FWObject* obj)
{
    ObjectSignature anon_sig = sig;
    anon_sig.object_name = "";
    QString as = anon_sig.toString();
    if (anon_object_registry.count(as) > 0) anon_object_registry.remove(as);

    named_object_registry[sig.toString()] = (obj!=NULL) ? obj->getId() : -1;
}
