createVideoObject(Global_as& gl)
{
    as_object* obj = getObjectWithPrototype(gl, NSV::CLASS_VIDEO);
    as_object* proto = obj->get_prototype();
    if (proto) {
        attachPrototypeProperties(*proto);
    }
    return obj;
}
