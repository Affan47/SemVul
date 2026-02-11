bNext_clicked_cb( GtkButton*, gpointer)
{
        if ( next(HTmpi) != channels_tmp.end() ) {
                widgets_to_current_channel_data();
                ++HTmpi;
                ++channel_no;
                current_channel_data_to_widgets();
        }
        sensitize_channel_nav_buttons();
}
