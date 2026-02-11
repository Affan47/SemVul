gwy_shader_destroy(GtkObject *object)
{
    GwyShader *shader;

    shader = GWY_SHADER(object);
    if (shader->gradient) {
        g_signal_handler_disconnect(shader->gradient,
                                    shader->gradient_change_id);
        gwy_resource_release(GWY_RESOURCE(shader->gradient));
        shader->gradient = NULL;
    }

    GTK_OBJECT_CLASS(gwy_shader_parent_class)->destroy(object);
}
