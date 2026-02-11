xmlnode_cloneNode(const fn_call& fn)
{
    XMLNode_as* ptr = ensure<ThisIsNative<XMLNode_as> >(fn);

    bool deep = false;
    if (fn.nargs > 0) deep = toBool(fn.arg(0), getVM(fn));

    as_object* newnode = ptr->cloneNode(deep)->object();
    return as_value(newnode);
}
