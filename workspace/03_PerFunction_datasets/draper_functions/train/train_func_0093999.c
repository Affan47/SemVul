net_options(){
    uMenu net_menu("$network_opts_text");

    uMenuItemInt high_port
    (&net_menu,"$network_opts_maxport_text",
     "$network_opts_maxport_help",
     gServerBrowser::highPort,1024,65536);

    uMenuItemInt low_port
    (&net_menu,"$network_opts_minport_text",
     "$network_opts_minport_help",
     gServerBrowser::lowPort,1024,65536);


    uMenuItemInt out_rate
    (&net_menu,"$network_opts_outrate_text",
     "$network_opts_outrate_help",
     sn_maxRateOut,1,20);


    uMenuItemInt in_rate
    (&net_menu,"$network_opts_inrate_text",
     "$network_opts_inrate_help",
     sn_maxRateIn,1,20);


    uMenuItemToggle po2
    (&net_menu,"$network_opts_predict_text",
     "$network_opts_predict_help",
     sr_predictObjects);

    uMenuItemToggle lm2
    (&net_menu,"$network_opts_lagometer_text",
     "$network_opts_lagometer_help",
     sr_laggometer);

    uMenuItemToggle ai
    (&net_menu,"$network_opts_axesindicator_text",
     "$network_opts_axesindicator_help",
     sg_axesIndicator);


    uMenuItemInt p_s
    (&net_menu,"$network_opts_pingchar_text",
     "$network_opts_pingchar_help",
     pingCharity,0,300,20);

    net_menu.Enter();

    if (gServerBrowser::lowPort > gServerBrowser::highPort)
        gServerBrowser::highPort = gServerBrowser::lowPort;
}
