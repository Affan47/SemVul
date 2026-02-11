glfwSetInputMode(GLFWwindow* handle, int mode, int value)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _GLFW_REQUIRE_INIT();

    switch (mode)
    {
        case GLFW_CURSOR:
        {
            if (value != GLFW_CURSOR_NORMAL &&
                value != GLFW_CURSOR_HIDDEN &&
                value != GLFW_CURSOR_DISABLED)
            {
                _glfwInputError(GLFW_INVALID_ENUM,
                                "Invalid cursor mode %i",
                                value);
                return;
            }

            if (window->cursorMode == value)
                return;

            window->cursorMode = value;

            _glfwPlatformGetCursorPos(window,
                                      &window->virtualCursorPosX,
                                      &window->virtualCursorPosY);

            if (_glfwPlatformWindowFocused(window))
                _glfwPlatformSetCursorMode(window, value);

            return;
        }

        case GLFW_STICKY_KEYS:
        {
            if (window->stickyKeys == value)
                return;

            if (!value)
            {
                int i;


                for (i = 0;  i <= GLFW_KEY_LAST;  i++)
                {
                    if (window->keys[i] == _GLFW_STICK)
                        window->keys[i] = GLFW_RELEASE;
                }
            }

            window->stickyKeys = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        }

        case GLFW_STICKY_MOUSE_BUTTONS:
        {
            if (window->stickyMouseButtons == value)
                return;

            if (!value)
            {
                int i;


                for (i = 0;  i <= GLFW_MOUSE_BUTTON_LAST;  i++)
                {
                    if (window->mouseButtons[i] == _GLFW_STICK)
                        window->mouseButtons[i] = GLFW_RELEASE;
                }
            }

            window->stickyMouseButtons = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        }
    }

    _glfwInputError(GLFW_INVALID_ENUM, "Invalid input mode %i", mode);
}
