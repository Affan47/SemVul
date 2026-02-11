updateTime(time_t display_time) {

    if(display_time == 0) {
        displaydate = "";
        return;
    }


    char datestr[256];
    struct tm* timeinfo = localtime ( &display_time );

    strftime(datestr, 256, gGourceSettings.date_format.c_str(), timeinfo);
    displaydate = datestr;


    int date_offset = (int) fontmedium.getWidth(displaydate) * 0.5;
    if(abs(date_x_offset - date_offset) > 5) date_x_offset = date_offset;
}
