timeformat(int duration) {
    int hours   = duration / 3600;
    int minutes = (duration - 3600 * hours) / 60;
    int seconds = duration % 60;
    if (hours > 0)
        return ecl::strf("%d:%02d'%02d\"", hours, minutes, seconds);
    else
        return ecl::strf("%d'%02d\"", minutes, seconds);
}
