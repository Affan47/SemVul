ifec_net_transmit ( struct net_device *netdev,
                               struct io_buffer *iobuf )
{
	struct ifec_private *priv = netdev->priv;
	struct ifec_tcb *tcb = priv->tcb_head->next;
	unsigned long ioaddr = priv->ioaddr;

	DBGP ( "ifec_net_transmit\n" );


	if ( tcb->status || tcb->iob ) {
		DBG ( "TX overflow\n" );
		return -ENOBUFS;
	}

	DBG2 ( "transmitting packet (%d bytes). status = %hX, cmd=%hX\n",
		iob_len ( iobuf ), tcb->status, inw ( ioaddr + SCBCmd ) );

	tcb->command   = CmdSuspend | CmdTx | CmdTxFlex;
	tcb->count     = 0x01208000;
	tcb->tbd_addr0 = virt_to_bus ( iobuf->data );
	tcb->tbd_size0 = 0x3FFF & iob_len ( iobuf );
	tcb->iob = iobuf;

	ifec_tx_wake ( netdev );


	priv->tcb_head = tcb;

	return 0;
}
