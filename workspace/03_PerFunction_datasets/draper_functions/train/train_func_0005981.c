dc_unsafeWrite(int fd)
{
	struct vsp_node *node;

	node = get_vsp_node(fd);
	if (node != NULL) {
		dc_debug(DC_INFO, "Unsafe write for [%d].",node->queueID);
		node->unsafeWrite = 1;
		m_unlock(&node->mux);
	}

	return;
}
