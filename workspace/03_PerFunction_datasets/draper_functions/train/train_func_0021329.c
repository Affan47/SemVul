_glfwPlatformGetWindowFrameSize(_GLFWwindow* window,
                                     int* left, int* top,
                                     int* right, int* bottom)
{
    long* extents = NULL;

    if (window->monitor || !window->decorated)
        return;

    if (_glfw.x11.NET_FRAME_EXTENTS == None)
        return;

    if (!_glfwPlatformWindowVisible(window) &&
        _glfw.x11.NET_REQUEST_FRAME_EXTENTS)
    {
        XEvent event;
        double timeout = 0.5;


        sendEventToWM(window, _glfw.x11.NET_REQUEST_FRAME_EXTENTS,
                      0, 0, 0, 0, 0);


        while (!XCheckIfEvent(_glfw.x11.display,
                              &event,
                              isFrameExtentsEvent,
                              (XPointer) window))
        {
            if (!waitForEvent(&timeout))
            {
                _glfwInputError(GLFW_PLATFORM_ERROR,
                                "X11: The window manager has a broken _NET_REQUEST_FRAME_EXTENTS implementation; please report this issue");
                return;
            }
        }
    }

    if (_glfwGetWindowPropertyX11(window->x11.handle,
                                  _glfw.x11.NET_FRAME_EXTENTS,
                                  XA_CARDINAL,
                                  (unsigned char**) &extents) == 4)
    {
        if (left)
            *left = extents[0];
        if (top)
            *top = extents[2];
        if (right)
            *right = extents[1];
        if (bottom)
            *bottom = extents[3];
    }

    if (extents)
        XFree(extents);
}
