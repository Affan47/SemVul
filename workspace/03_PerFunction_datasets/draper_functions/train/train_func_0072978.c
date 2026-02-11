gnc_item_edit_realize (GnomeCanvasItem *item)
{
    GnomeCanvas *canvas = item->canvas;
    GdkWindow *window;
    GncItemEdit *item_edit;

    if (GNOME_CANVAS_ITEM_CLASS (gnc_item_edit_parent_class)->realize)
        (*GNOME_CANVAS_ITEM_CLASS
         (gnc_item_edit_parent_class)->realize) (item);

    item_edit = GNC_ITEM_EDIT (item);
    window = GTK_WIDGET (canvas)->window;

    item_edit->gc = gdk_gc_new (window);
}
