format_time(char* str, int seconds, int accurate) {

    int hour, min, sec;

    if (seconds > 86400 && accurate == 0) {
        sprintf(str, "~%uh", (unsigned int)(seconds / 3600.0));
    } else {

        sec = seconds % 3600;
        hour = (seconds - sec) / 3600;
        min =  sec / 60;
        sec = sec % 60;

        if (hour == 0) {
            sprintf(str, "%02d:%02d", min, sec);
        } else {
            sprintf(str, "%02d:%02d:%02d", hour, min, sec);
        }

    }

}
