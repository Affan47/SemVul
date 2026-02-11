mtnic_close(struct net_device *dev)
{
	struct mtnic_port *priv = netdev_priv(dev);
	int err = 0;
	DBG("Close called for port:%d\n", priv->port);

	if ( ( priv->state == CARD_UP ) ||
	     ( priv->state == CARD_LINK_DOWN ) ) {


		err |= mtnic_SET_PORT_STATE(priv, priv->port, 0);


		mdelay(5);


		err |= mtnic_RELEASE_RESOURCE(priv, priv->port,
					      MTNIC_IF_RESOURCE_TYPE_RX_RING, 0);


		err |= mtnic_RELEASE_RESOURCE(priv, priv->port,
					      MTNIC_IF_RESOURCE_TYPE_TX_RING, 0);


		err |= mtnic_RELEASE_RESOURCE(priv, priv->port,
					      MTNIC_IF_RESOURCE_TYPE_CQ, 0);
		err |= mtnic_RELEASE_RESOURCE(priv, priv->port,
					      MTNIC_IF_RESOURCE_TYPE_CQ, 1);
		if (err) {
			DBG("Close reported error %d\n", err);
		}

		mdelay ( 10 );


		free_memblock(priv->tx_ring.buf, priv->tx_ring.buf_size);
		iounmap(priv->tx_ring.txcq_db);
		free_memblock(priv->cq[1].buf, priv->cq[1].buf_size);
		free_memblock(priv->cq[1].db, sizeof(struct mtnic_cq_db_record));
		free_memblock(priv->rx_ring.buf, priv->rx_ring.buf_size);
		free_memblock(priv->rx_ring.db, sizeof(struct mtnic_cq_db_record));
		free_memblock(priv->cq[0].buf, priv->cq[0].buf_size);
		free_memblock(priv->cq[0].db, sizeof(struct mtnic_cq_db_record));


		mtnic_free_io_buffers(&priv->rx_ring);


	}

	priv->state = CARD_INITIALIZED;

}
