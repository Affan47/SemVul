getDataRoles ( const TCGNode* node, bool onlyDet )
{
	Roles.clear();
	for ( DlCompletionTree::const_edge_iterator p = node->begin(), p_end = node->end(); p != p_end; ++p )
		if ( likely(!(*p)->isIBlocked()) && (*p)->getArcEnd()->isDataNode() && (!onlyDet || (*p)->getDep().empty()) )
			addAll(DRs.get((*p)->getRole()->getEntity()));
	return Roles;
}
