ndmp_3to9_fh_add_node_free_request (ndmp9_fh_add_node_request *request9)
{
    if (request9) {
	if(request9->nodes.nodes_val) {
	    NDMOS_API_FREE(request9->nodes.nodes_val);
	}
	request9->nodes.nodes_val = 0;
    }
    return 0;
}
