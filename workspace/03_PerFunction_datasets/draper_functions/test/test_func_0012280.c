update_login1_seat (Login1Seat *login1_seat)
{
    if (!config_get_boolean (config_get_instance (), "LightDM", "logind-check-graphical") ||
        login1_seat_get_can_graphical (login1_seat))
    {
        Seat *seat;


        seat = display_manager_get_seat (display_manager, login1_seat_get_id (login1_seat));
        if (seat)
        {
            if (seat_get_is_stopping (seat))
                g_signal_connect (seat, "stopped", G_CALLBACK (seat_stopped_cb), login1_seat);
            return TRUE;
        }

        return add_login1_seat (login1_seat);
    }
    else
    {
        remove_login1_seat (login1_seat);
        return TRUE;
    }
}
