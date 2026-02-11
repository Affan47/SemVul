set_function(AW_function mode)
{
    if (function != mode) {
        switch(mode) {
            case AW_XOR:
                XSetFunction(common->display,gc,GXxor);
                break;
            case AW_COPY:
                XSetFunction(common->display,gc,GXcopy);
                break;
        }
        function = mode;
        set_foreground_color(color);
    }
}
