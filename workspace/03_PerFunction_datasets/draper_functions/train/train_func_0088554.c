view_helper_set_node(ViewHelper *self, GeglNode *node)
{
    if (self->node == node)
        return;

    if (self->node)
        g_object_unref(self->node);

    if (node) {
        g_object_ref(node);
        self->node = node;

        g_signal_connect_object(self->node, "computed",
                                G_CALLBACK(computed_event),
                                self, 0);
        g_signal_connect_object(self->node, "invalidated",
                                G_CALLBACK(invalidated_event),
                                self, 0);

        if (self->processor)
            g_object_unref(self->processor);

        GeglRectangle bbox = gegl_node_get_bounding_box(self->node);
        self->processor = gegl_node_new_processor(self->node, &bbox);

        update_autoscale(self);
        trigger_processing(self, bbox);

    } else
        self->node = NULL;
}
