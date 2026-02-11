niu_ethflow_to_class(int flow_type, u64 *class)
{
	switch (flow_type) {
	case TCP_V4_FLOW:
		*class = CLASS_CODE_TCP_IPV4;
		break;
	case UDP_V4_FLOW:
		*class = CLASS_CODE_UDP_IPV4;
		break;
	case AH_ESP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
		*class = CLASS_CODE_AH_ESP_IPV4;
		break;
	case SCTP_V4_FLOW:
		*class = CLASS_CODE_SCTP_IPV4;
		break;
	case TCP_V6_FLOW:
		*class = CLASS_CODE_TCP_IPV6;
		break;
	case UDP_V6_FLOW:
		*class = CLASS_CODE_UDP_IPV6;
		break;
	case AH_ESP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
		*class = CLASS_CODE_AH_ESP_IPV6;
		break;
	case SCTP_V6_FLOW:
		*class = CLASS_CODE_SCTP_IPV6;
		break;
	default:
		return 0;
	}

	return 1;
}
