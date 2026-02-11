flps_draw_input( FL_OBJECT * ob )
{
    long col = ob->focus ? ob->col2 : ob->col1;

    ob->align &= ~FL_ALIGN_INSIDE;
    ps_draw_box( ob->boxtype, ob->x, ob->y, ob->w, ob->h, col, ob->bw );
    ps_draw_object_label_beside( ob );
}
