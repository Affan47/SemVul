add_death(object *victim, object *killer) {
    int vid, kid, map_id;
    char *sql;

    if (!victim || !killer)
        return;
    if (victim->type != PLAYER && killer->type != PLAYER) {

        object *owner = cf_object_get_object_property(killer, CFAPI_OBJECT_PROP_OWNER);
        if (owner != NULL && owner->type == PLAYER)
            killer = owner;
        else
            return;
    }

    vid = get_living_id(victim);
    kid = get_living_id(killer);
    map_id = get_map_id(victim->map);
    sql = sqlite3_mprintf("insert into kill_event values( %d, %d, %d, %d, %d, %d)", time(NULL), vid, victim->level, map_id, kid, killer->level);
    do_sql(sql);
    sqlite3_free(sql);
}
