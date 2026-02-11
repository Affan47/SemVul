obj_timer_checks(struct obj *otmp,
                 xchar x, xchar y,
                 int force)
{
    long tleft = 0L;
    short action = ROT_CORPSE;
    bool restart_timer = false;
    bool on_floor = (otmp->where == OBJ_FLOOR);
    bool buried = (otmp->where == OBJ_BURIED);


    if (otmp->otyp == CORPSE && (on_floor || buried) && is_ice(x,y)) {
        tleft = stop_timer(action, (void *)otmp);
        if (tleft == 0L) {
            action = REVIVE_MON;
            tleft = stop_timer(action, (void *)otmp);
        }
        if (tleft != 0L) {
            long age;

            tleft = tleft - monstermoves;

            ON_ICE(otmp) = 1;
#ifdef DEBUG_EFFECTS
            pline("%s is now on ice at %d,%d.", The(xname(otmp)),x,y);
#endif

            tleft *= ROT_ICE_ADJUSTMENT;
            restart_timer = true;

            age = monstermoves - otmp->age;
            otmp->age = monstermoves - (age * ROT_ICE_ADJUSTMENT);
        }
    }

    else if ((force < 0) ||
             (otmp->otyp == CORPSE && ON_ICE(otmp) &&
              ((on_floor && !is_ice(x,y)) || !on_floor))) {
        tleft = stop_timer(action, (void *)otmp);
        if (tleft == 0L) {
            action = REVIVE_MON;
            tleft = stop_timer(action, (void *)otmp);
        }
        if (tleft != 0L) {
            long age;

            tleft = tleft - monstermoves;
            ON_ICE(otmp) = 0;
#ifdef DEBUG_EFFECTS
            pline("%s is no longer on ice at %d,%d.", The(xname(otmp)),x,y);
#endif

            tleft /= ROT_ICE_ADJUSTMENT;
            restart_timer = true;

            age = monstermoves - otmp->age;
            otmp->age = otmp->age + (age / ROT_ICE_ADJUSTMENT);
        }
    }

    if (restart_timer)
            start_timer(tleft, TIMER_OBJECT, action, (void *)otmp);
}
