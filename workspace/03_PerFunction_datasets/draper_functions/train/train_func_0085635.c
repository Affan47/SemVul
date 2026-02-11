destroyContextOSMesa(_GLFWwindow* window)
{
    if (window->context.osmesa.handle)
    {
        OSMesaDestroyContext(window->context.osmesa.handle);
        window->context.osmesa.handle = NULL;
    }

    if (window->context.osmesa.buffer)
    {
        free(window->context.osmesa.buffer);
        window->context.osmesa.width = 0;
        window->context.osmesa.height = 0;
    }
}
