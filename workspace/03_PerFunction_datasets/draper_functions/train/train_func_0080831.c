glfwSetGammaRamp(GLFWmonitor* handle, const GLFWgammaramp* ramp)
{
    _GLFWmonitor* monitor = (_GLFWmonitor*) handle;
    assert(monitor != NULL);
    assert(ramp != NULL);
    assert(ramp->size > 0);
    assert(ramp->red != NULL);
    assert(ramp->green != NULL);
    assert(ramp->blue != NULL);

    if (ramp->size <= 0)
    {
        _glfwInputError(GLFW_INVALID_VALUE,
                        "Invalid gamma ramp size %i",
                        ramp->size);
        return;
    }

    _GLFW_REQUIRE_INIT();

    if (!monitor->originalRamp.size)
        _glfwPlatformGetGammaRamp(monitor, &monitor->originalRamp);

    _glfwPlatformSetGammaRamp(monitor, ramp);
}
