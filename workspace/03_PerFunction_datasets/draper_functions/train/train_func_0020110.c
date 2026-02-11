ql_set_routing_reg(struct ql_adapter *qdev, u32 index, u32 mask,
			      int enable)
{
	int status = -EINVAL;
	u32 value = 0;

	switch (mask) {
	case RT_IDX_CAM_HIT:
		{
			value = RT_IDX_DST_CAM_Q |
			    RT_IDX_TYPE_NICQ |
			    (RT_IDX_CAM_HIT_SLOT << RT_IDX_IDX_SHIFT);
			break;
		}
	case RT_IDX_VALID:
		{
			value = RT_IDX_DST_DFLT_Q |
			    RT_IDX_TYPE_NICQ |
			    (RT_IDX_PROMISCUOUS_SLOT << RT_IDX_IDX_SHIFT);
			break;
		}
	case RT_IDX_ERR:
		{
			value = RT_IDX_DST_DFLT_Q |
			    RT_IDX_TYPE_NICQ |
			    (RT_IDX_ALL_ERR_SLOT << RT_IDX_IDX_SHIFT);
			break;
		}
	case RT_IDX_IP_CSUM_ERR:
		{
			value = RT_IDX_DST_DFLT_Q |
				RT_IDX_TYPE_NICQ |
				(RT_IDX_IP_CSUM_ERR_SLOT <<
				RT_IDX_IDX_SHIFT);
			break;
		}
	case RT_IDX_TU_CSUM_ERR:
		{
			value = RT_IDX_DST_DFLT_Q |
				RT_IDX_TYPE_NICQ |
				(RT_IDX_TCP_UDP_CSUM_ERR_SLOT <<
				RT_IDX_IDX_SHIFT);
			break;
		}
	case RT_IDX_BCAST:
		{
			value = RT_IDX_DST_DFLT_Q |
			    RT_IDX_TYPE_NICQ |
			    (RT_IDX_BCAST_SLOT << RT_IDX_IDX_SHIFT);
			break;
		}
	case RT_IDX_MCAST:
		{
			value = RT_IDX_DST_DFLT_Q |
			    RT_IDX_TYPE_NICQ |
			    (RT_IDX_ALLMULTI_SLOT << RT_IDX_IDX_SHIFT);
			break;
		}
	case RT_IDX_MCAST_MATCH:
		{
			value = RT_IDX_DST_DFLT_Q |
			    RT_IDX_TYPE_NICQ |
			    (RT_IDX_MCAST_MATCH_SLOT << RT_IDX_IDX_SHIFT);
			break;
		}
	case RT_IDX_RSS_MATCH:
		{
			value = RT_IDX_DST_RSS |
			    RT_IDX_TYPE_NICQ |
			    (RT_IDX_RSS_MATCH_SLOT << RT_IDX_IDX_SHIFT);
			break;
		}
	case 0:
		{
			value = RT_IDX_DST_DFLT_Q |
			    RT_IDX_TYPE_NICQ |
			    (index << RT_IDX_IDX_SHIFT);
			break;
		}
	default:
		netif_err(qdev, ifup, qdev->ndev,
			  "Mask type %d not yet supported.\n", mask);
		status = -EPERM;
		goto exit;
	}

	if (value) {
		status = ql_wait_reg_rdy(qdev, RT_IDX, RT_IDX_MW, 0);
		if (status)
			goto exit;
		value |= (enable ? RT_IDX_E : 0);
		ql_write32(qdev, RT_IDX, value);
		ql_write32(qdev, RT_DATA, enable ? mask : 0);
	}
exit:
	return status;
}
