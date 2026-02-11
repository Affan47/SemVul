lock_and_hide_doors(object **doorlist, mapstruct *map, int opts, RMParms *RP) {
    object *door;
    int i;


    if (opts&DOORED) {
        for (i = 0, door = doorlist[0]; doorlist[i] != NULL; i++) {
            object *new_door = create_archetype("locked_door1");
            char keybuf[256];

            door = doorlist[i];
            new_door->face = door->face;
            object_remove(door);
            object_free_drop_inventory(door);
            doorlist[i] = new_door;
            object_insert_in_map_at(new_door, map, NULL, 0, door->x, door->y);

            snprintf(keybuf, 256, "%d", (int)RANDOM());
            if (keyplace(map, new_door->x, new_door->y, keybuf, NO_PASS_DOORS, 2, RP))
                new_door->slaying = add_string(keybuf);
        }
        for (i = 0; doorlist[i] != NULL; i++)
            remove_adjacent_doors(doorlist[i]);
    }


    if (opts&HIDDEN) {
        for (i = 0, door = doorlist[0]; doorlist[i] != NULL; i++) {
            object *wallface;

            door = doorlist[i];
            wallface = retrofit_joined_wall(map, door->x, door->y, 1, RP);
            if (wallface != NULL) {
                retrofit_joined_wall(map, door->x-1, door->y, 0, RP);
                retrofit_joined_wall(map, door->x+1, door->y, 0, RP);
                retrofit_joined_wall(map, door->x, door->y-1, 0, RP);
                retrofit_joined_wall(map, door->x, door->y+1, 0, RP);
                door->face = wallface->face;
                if (!QUERY_FLAG(wallface, FLAG_REMOVED))
                    object_remove(wallface);
                object_free_drop_inventory(wallface);
            }
        }
    }
}
