bkn_resume_tx(bkn_switch_info_t *sinfo)
{
    struct list_head *list;
    bkn_priv_t *priv = netdev_priv(sinfo->dev);


    if (netif_queue_stopped(priv->dev) && sinfo->tx.free > 1) {
        netif_wake_queue(priv->dev);
    }

    list_for_each(list, &sinfo->ndev_list) {
        priv = (bkn_priv_t *)list;
        if (netif_queue_stopped(priv->dev) && sinfo->tx.free > 1) {
            netif_wake_queue(priv->dev);
        }
    }
}
