wakeup_main_loop(struct ntb_main_context *mc)
{
        if (!pthread_equal(pthread_self(), mc->main_thread))
                send_async_byte(mc, 'W');
}
