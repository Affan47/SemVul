TXT_GUIMainLoop(void)
{
    main_loop_running = 1;

    while (main_loop_running)
    {
        TXT_DispatchEvents();


        if (num_windows <= 0)
        {
            TXT_ExitMainLoop();
        }

        TXT_DrawDesktop();


        if (periodic_callback == NULL)
        {
            TXT_Sleep(0);
        }
        else
        {
            TXT_Sleep(periodic_callback_period);

            periodic_callback(periodic_callback_data);
        }
    }
}
