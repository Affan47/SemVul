destroyContextGLX(_GLFWwindow* window)
{
    if (window->context.glx.window)
    {
        glXDestroyWindow(_glfw.x11.display, window->context.glx.window);
        window->context.glx.window = None;
    }

    if (window->context.glx.handle)
    {
        glXDestroyContext(_glfw.x11.display, window->context.glx.handle);
        window->context.glx.handle = NULL;
    }
}
