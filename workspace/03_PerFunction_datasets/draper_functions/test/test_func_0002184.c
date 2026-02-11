gwy_shader_timer(GwyShader *shader)
{
    if (shader->update_policy == GTK_UPDATE_DELAYED)
        g_signal_emit(shader, shader_signals[ANGLE_CHANGED], 0);

    shader->timer_id = 0;
    return FALSE;
}
