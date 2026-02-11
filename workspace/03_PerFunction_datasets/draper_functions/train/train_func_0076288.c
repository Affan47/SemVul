update_character_choose(const char *name, const char *class,
                             const char *race, const char *face,
                             const char *party, const char *map,
                             int level, int faceno)
{
    GtkTreeIter iter;

    gtk_list_store_append(character_store, &iter);


    if (pixmaps[faceno] == pixmaps[0]) {
        gtk_list_store_set(character_store, &iter,
                       CHAR_NAME, name,
                       CHAR_CLASS, class,
                       CHAR_RACE, race,
                       CHAR_IMAGE, face,
                       CHAR_PARTY, party,
                       CHAR_MAP, map,
                       CHAR_LEVEL, level,
                       -1);
    } else {
        gtk_list_store_set(character_store, &iter,
                       CHAR_ICON, pixmaps[faceno]->icon_image,
                       CHAR_NAME, name,
                       CHAR_CLASS, class,
                       CHAR_RACE, race,
                       CHAR_IMAGE, face,
                       CHAR_PARTY, party,
                       CHAR_MAP, map,
                       CHAR_LEVEL, level,
                       -1);
    }
}
