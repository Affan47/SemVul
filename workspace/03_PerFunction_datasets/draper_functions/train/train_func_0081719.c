monster_run_att(int dir, object *ob, object *enemy, object *part, rv_vector *rv) {
    if ((monster_can_hit(part, enemy, rv) && ob->move_status < 20) || ob->move_status < 20) {
        ob->move_status++;
        return (dir);
    } else if (ob->move_status > 20)
        ob->move_status = 0;
    return absdir(dir+4);
}
