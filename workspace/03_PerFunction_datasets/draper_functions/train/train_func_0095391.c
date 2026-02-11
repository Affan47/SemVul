attachInterface(as_object& obj)
{
    GNASH_REPORT_FUNCTION;
    Global_as& gl = getGlobal(obj);

    obj.init_member("lirc_init", gl.createFunction(lirc_ext_init));
    obj.init_member("lirc_getKey", gl.createFunction(lirc_ext_getkey));
    obj.init_member("lirc_getButton", gl.createFunction(lirc_ext_getbutton));
}
