__drm_atomic_helper_connector_reset(struct drm_connector *connector,
				    struct drm_connector_state *conn_state)
{
	if (conn_state)
		conn_state->connector = connector;

	connector->state = conn_state;
}
