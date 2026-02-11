__lb_run_test(struct net_device *ndev,
			 enum hnae_loop loop_mode)
{
#define NIC_LB_TEST_PKT_NUM_PER_CYCLE 1
#define NIC_LB_TEST_RING_ID 0
#define NIC_LB_TEST_FRAME_SIZE 128

#define NIC_LB_TEST_NO_MEM_ERR 1
#define NIC_LB_TEST_TX_CNT_ERR 2
#define NIC_LB_TEST_RX_CNT_ERR 3
#define NIC_LB_TEST_RX_PKG_ERR 4
	struct hns_nic_priv *priv = netdev_priv(ndev);
	struct hnae_handle *h = priv->ae_handle;
	int i, j, lc, good_cnt, ret_val = 0;
	unsigned int size;
	netdev_tx_t tx_ret_val;
	struct sk_buff *skb;

	size = NIC_LB_TEST_FRAME_SIZE;

	skb = alloc_skb(size, GFP_KERNEL);
	if (!skb)
		return NIC_LB_TEST_NO_MEM_ERR;


	(void)skb_put(skb, size);
	__lb_other_process(NULL, skb);
	skb->queue_mapping = NIC_LB_TEST_RING_ID;

	lc = 1;
	for (j = 0; j < lc; j++) {

		good_cnt = 0;

		for (i = 0; i < NIC_LB_TEST_PKT_NUM_PER_CYCLE; i++) {
			(void)skb_get(skb);

			tx_ret_val = (netdev_tx_t)hns_nic_net_xmit_hw(
				ndev, skb,
				&tx_ring_data(priv, skb->queue_mapping));
			if (tx_ret_val == NETDEV_TX_OK)
				good_cnt++;
			else
				break;
		}
		if (good_cnt != NIC_LB_TEST_PKT_NUM_PER_CYCLE) {
			ret_val = NIC_LB_TEST_TX_CNT_ERR;
			dev_err(priv->dev, "%s sent fail, cnt=0x%x, budget=0x%x\n",
				hns_nic_test_strs[loop_mode], good_cnt,
				NIC_LB_TEST_PKT_NUM_PER_CYCLE);
			break;
		}


		msleep(100);

		good_cnt = __lb_clean_rings(priv,
					    h->q_num, h->q_num * 2 - 1,
					    NIC_LB_TEST_PKT_NUM_PER_CYCLE);
		if (good_cnt != NIC_LB_TEST_PKT_NUM_PER_CYCLE) {
			ret_val = NIC_LB_TEST_RX_CNT_ERR;
			dev_err(priv->dev, "%s recv fail, cnt=0x%x, budget=0x%x\n",
				hns_nic_test_strs[loop_mode], good_cnt,
				NIC_LB_TEST_PKT_NUM_PER_CYCLE);
			break;
		}
		(void)__lb_clean_rings(priv,
				       NIC_LB_TEST_RING_ID, NIC_LB_TEST_RING_ID,
				       NIC_LB_TEST_PKT_NUM_PER_CYCLE);
	}


	kfree_skb(skb);

	return ret_val;
}
