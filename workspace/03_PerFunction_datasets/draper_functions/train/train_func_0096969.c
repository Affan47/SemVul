TXT_RaiseWindow(txt_window_t *window)
{
    int i;

    for (i = 0; i < num_windows - 1; ++i)
    {
        if (all_windows[i] == window)
        {
            all_windows[i] = all_windows[i + 1];
            all_windows[i + 1] = window;

            if (i == num_windows - 2)
            {
                TXT_SetWindowFocus(all_windows[i], 0);
                TXT_SetWindowFocus(window, 1);
            }

            return 1;
        }
    }


    return 0;
}
