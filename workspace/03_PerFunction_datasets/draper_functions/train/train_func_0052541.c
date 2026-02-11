removeRCPNode( RCPNode* rcp_node )
{


  TEUCHOS_ASSERT(rcp_node_list());
  typedef rcp_node_list_t::iterator itr_t;
  typedef std::pair<itr_t, itr_t> itr_itr_t;

  const itr_itr_t itr_itr =
    rcp_node_list()->equal_range(get_map_key_void_ptr(rcp_node));
  const bool rcp_node_exists = itr_itr.first != itr_itr.second;

#ifdef HAVE_TEUCHOS_DEBUG_RCP_NODE_TRACING


  TEUCHOS_RCPNODE_REMOVE_RCPNODE(!rcp_node_exists, rcp_node);
#else


#endif

  if (rcp_node_exists) {
#ifdef RCP_NODE_DEBUG_TRACE_PRINT
    std::cerr
      << "RCPNodeTracer::removeRCPNode(...): Removing "
      << convertRCPNodeToString(rcp_node) << " ...\n";
#endif
    bool foundRCPNode = false;
    for(itr_t itr = itr_itr.first; itr != itr_itr.second; ++itr) {
      if (itr->second.nodePtr == rcp_node) {
        rcp_node_list()->erase(itr);
        ++loc_rcpNodeStatistics().totalNumRCPNodeDeletions;
        foundRCPNode = true;
        break;
      }
    }

    TEUCHOS_RCPNODE_REMOVE_RCPNODE(!foundRCPNode, rcp_node);
  }

}
