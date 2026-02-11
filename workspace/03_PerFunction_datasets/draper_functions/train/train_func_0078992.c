bd_start_bdj(BLURAY *bd, const char *start_object)
{
    unsigned ii;

    if (!bd || !bd->index) {
        return 0;
    }


    if (bd->index->first_play.object_type == indx_object_type_bdj &&
        !strcmp(start_object, bd->index->first_play.bdj.name)) {
        return _start_bdj(bd, BLURAY_TITLE_FIRST_PLAY);
    }


    if (bd->index->first_play.object_type == indx_object_type_bdj &&
        !strcmp(start_object, bd->index->top_menu.bdj.name)) {
        return _start_bdj(bd, BLURAY_TITLE_TOP_MENU);
    }


    for (ii = 0; ii < bd->index->num_titles; ii++) {
        INDX_TITLE *t = &bd->index->titles[ii];

        if (t->object_type == indx_object_type_bdj &&
            !strcmp(start_object, t->bdj.name)) {
            return _start_bdj(bd, ii + 1);
        }
    }

    BD_DEBUG(DBG_BLURAY | DBG_CRIT, "No %s.bdjo in disc index\n", start_object);
    return 0;
 }
