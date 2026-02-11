ck_seat_constructor (GType                  type,
                     guint                  n_construct_properties,
                     GObjectConstructParam *construct_properties)
{
        CkSeat      *seat;
        CkSeatClass *klass;

        klass = CK_SEAT_CLASS (g_type_class_peek (CK_TYPE_SEAT));

        seat = CK_SEAT (G_OBJECT_CLASS (ck_seat_parent_class)->constructor (type,
                                                                            n_construct_properties,
                                                                            construct_properties));

        if (seat->priv->kind == CK_SEAT_KIND_STATIC) {
                seat->priv->vt_monitor = ck_vt_monitor_new ();
                g_signal_connect (seat->priv->vt_monitor, "active-changed", G_CALLBACK (active_vt_changed), seat);
        }

        return G_OBJECT (seat);
}
