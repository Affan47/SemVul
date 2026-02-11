gr_scroll(object *obj)
{
    short percent;
    int i;
    static short per[SCROLS] = {
	5, 11, 16, 21, 36, 44, 51, 56, 65, 74, 80, 85
    };

    percent = get_rand(0, 85);
    obj->what_is = SCROL;
    for (i = 0;; i++) {
	if (percent <= per[i]) {
	    obj->which_kind = i;
	    return;
	}
    }
}
