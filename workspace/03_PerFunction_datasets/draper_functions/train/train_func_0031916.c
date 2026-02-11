fc_ulp_close ( struct fc_ulp *ulp, int rc ) {

	DBGC ( ulp, "FCULP %s/%02x closed: %s\n",
	       fc_ntoa ( &ulp->peer->port_wwn ), ulp->type, strerror ( rc ) );


	assert ( list_empty ( &ulp->users ) );


	fc_link_stop ( &ulp->link );


	intf_shutdown ( &ulp->prli, rc );


	list_del ( &ulp->list );
	INIT_LIST_HEAD ( &ulp->list );
}
