_glfwRestoreVideoModeX11(_GLFWmonitor* monitor)
{
    if (_glfw.x11.randr.available && !_glfw.x11.randr.monitorBroken)
    {
        XRRScreenResources* sr;
        XRRCrtcInfo* ci;

        if (monitor->x11.oldMode == None)
            return;

        sr = XRRGetScreenResourcesCurrent(_glfw.x11.display, _glfw.x11.root);
        ci = XRRGetCrtcInfo(_glfw.x11.display, sr, monitor->x11.crtc);

        XRRSetCrtcConfig(_glfw.x11.display,
                         sr, monitor->x11.crtc,
                         CurrentTime,
                         ci->x, ci->y,
                         monitor->x11.oldMode,
                         ci->rotation,
                         ci->outputs,
                         ci->noutput);

        XRRFreeCrtcInfo(ci);
        XRRFreeScreenResources(sr);

        monitor->x11.oldMode = None;
    }
}
