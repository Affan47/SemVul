monster_wait_att(int dir, object *ob, object *enemy, object *part, rv_vector *rv) {
    int inrange = monster_can_hit(part, enemy, rv);

    if (ob->move_status || inrange)
        ob->move_status++;

    if (ob->move_status == 0)
        return 0;
    else if (ob->move_status < 10)
        return dir;
    else if (ob->move_status < 15)
        return absdir(dir+4);
    ob->move_status = 0;
    return 0;
}
