feeder_hide(bool hide, size_t id1, size_t id2)
{
    size_t i;
    if(id1 > id2
            || id2 >= _feeder_nb)
        return;
    for(i = id1; i <= id2; ++i)
        _feeder_lines[i].show = !hide;
    curses_list_changed(true);
}
