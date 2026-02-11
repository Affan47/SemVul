synctex_node_v(synctex_node_t node){
	if (!node) {
		return 0;
	}
	return SYNCTEX_VERT(node);
}
