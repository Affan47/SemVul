parseEvents(const char *evtlist)
{
    memset(nonbreaking_events, 0, sizeof nonbreaking_events);

    const struct
    {
        uchar num;
        const char *name;
    } evttable[] =
        {
            { EVT_BREAK,				"break" },
            { EVT_DEBUG,				"debug" },
            { EVT_ERROR_PHY_FORCE_BREAK_TIMEOUT,	"error_phy_force_break_timeout" },
            { EVT_ERROR_PHY_MAX_BIT_LENGTH_DIFF,	"error_phy_max_bit_length_diff" },
            { EVT_ERROR_PHY_OPT_RECEIVE_TIMEOUT,	"error_phy_opt_receive_timeout" },
            { EVT_ERROR_PHY_OPT_RECEIVED_BREAK,		"error_phy_opt_received_break" },
            { EVT_ERROR_PHY_RECEIVED_BREAK,		"error_phy_received_break" },
            { EVT_ERROR_PHY_RECEIVE_TIMEOUT,		"error_phy_receive_timeout" },
            { EVT_ERROR_PHY_RELEASE_BREAK_TIMEOUT,	"error_phy_release_break_timeout" },
            { EVT_ERROR_PHY_SYNC_OUT_OF_RANGE,		"error_phy_sync_out_of_range" },
            { EVT_ERROR_PHY_SYNC_TIMEOUT,		"error_phy_sync_timeout" },
            { EVT_ERROR_PHY_SYNC_TIMEOUT_BAUD,		"error_phy_sync_timeout_baud" },
            { EVT_ERROR_PHY_SYNC_WAIT_TIMEOUT,		"error_phy_sync_wait_timeout" },
            { EVT_RESULT_PHY_NO_ACTIVITY,		"result_phy_no_activity" },
            { EVT_EXT_RESET,				"ext_reset" },
            { EVT_ICE_POWER_ERROR_STATE,		"ice_power_error_state" },
            { EVT_ICE_POWER_OK,				"ice_power_ok" },
            { EVT_IDR_DIRTY,				"idr_dirty" },
            { EVT_NONE,					"none" },
            { EVT_PDSB_BREAK,				"pdsb_break" },
            { EVT_PDSMB_BREAK,				"pdsmb_break" },
            { EVT_PROGRAM_BREAK,			"program_break" },
            { EVT_RUN,					"run" },
            { EVT_TARGET_POWER_OFF,			"target_power_off" },
            { EVT_TARGET_POWER_ON,			"target_power_on" },
            { EVT_TARGET_SLEEP,				"target_sleep" },
            { EVT_TARGET_WAKEUP,			"target_wakeup" },
        };


    const char *cp1, *cp2;
    cp1 = evtlist;
    while (*cp1 != '\0')
    {
        while (isspace(*cp1) || *cp1 == ',')
            cp1++;
        cp2 = cp1;
        while (*cp2 != '\0' && *cp2 != ',')
            cp2++;
        size_t l = cp2 - cp1;
        uchar evtval = 0;


        for (unsigned int i = 0; i < sizeof evttable / sizeof evttable[0]; i++)
        {
            if (strncmp(evttable[i].name, cp1, l) == 0)
            {
                evtval = evttable[i].num;
                break;
            }
        }
        if (evtval == 0)
        {
            fprintf(stderr, "Warning: event name %.*s not matched\n",
                    (int)l, cp1);
        }
        else
        {
            nonbreaking_events[evtval - EVT_BREAK] = true;
        }

        cp1 = cp2;
    }
}
