attachSharedObjectStaticInterface(as_object& o)
{
    VM& vm = getVM(o);

    const int flags = 0;

    Global_as& gl = getGlobal(o);
    o.init_member("getLocal", gl.createFunction(sharedobject_getLocal), flags);
    o.init_member("getRemote",
            gl.createFunction(sharedobject_getRemote), flags);

    const int hiddenOnly = PropFlags::dontEnum;

    o.init_member("deleteAll",  vm.getNative(2106, 206), hiddenOnly);
    o.init_member("getDiskUsage",  vm.getNative(2106, 207), hiddenOnly);
}
