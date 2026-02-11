instanceOfMatrix(const fn_call& fn)
{
    as_object* obj = ensure<ValidThis>(fn);

    as_function* ctor = getClassConstructor(fn, "flash.geom.Matrix");
    if (obj->instanceOf(ctor)) return obj;
    return 0;
}
