gdm_simple_slave_start_session_when_ready (GdmSimpleSlave *slave,
                                           const char     *service_name)
{
        if (slave->priv->start_session_when_ready) {
                slave->priv->waiting_to_start_session = FALSE;
                queue_start_session (slave, service_name);
        } else {
                slave->priv->waiting_to_start_session = TRUE;
        }
}
