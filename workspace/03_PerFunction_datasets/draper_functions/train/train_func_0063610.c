animate_look(void)
{
    gboolean valid;
    GtkTreeIter iter;
    item *tmp;
    static int inv_tick=0;


    if (!tick) {


        inv_tick++;
        if (inv_tick < 12) return;
        inv_tick=0;
    }


    valid = gtk_tree_model_get_iter_first (GTK_TREE_MODEL(store_look), &iter);

    while (valid) {
        gtk_tree_model_get (GTK_TREE_MODEL(store_look), &iter,
                          LIST_OBJECT, &tmp,
                          -1);


        if (tmp->animation_id >0 && tmp->anim_speed) {
            tmp->last_anim++;


            if (tmp->last_anim >= tmp->anim_speed) {
                tmp->anim_state++;
                if (tmp->anim_state >= animations[tmp->animation_id].num_animations)
                    tmp->anim_state=0;
                tmp->face = animations[tmp->animation_id].faces[tmp->anim_state];
                tmp->last_anim=0;


                gtk_tree_store_set(store_look, &iter,
                                   LIST_ICON, (GdkPixbuf*)pixmaps[tmp->face]->icon_image,
                                   -1);
            }
        }
        valid = gtk_tree_model_iter_next (GTK_TREE_MODEL(store_look), &iter);
    }
}
