on_timeout(unsigned long priv)
{
	struct r3964_info *pInfo = (void *)priv;

	switch (pInfo->state) {
	case R3964_TX_REQUEST:
		TRACE_PE("TX_REQUEST - timeout");
		retry_transmit(pInfo);
		break;
	case R3964_WAIT_ZVZ_BEFORE_TX_RETRY:
		put_char(pInfo, NAK);
		flush(pInfo);
		retry_transmit(pInfo);
		break;
	case R3964_WAIT_FOR_TX_ACK:
		TRACE_PE("WAIT_FOR_TX_ACK - timeout");
		retry_transmit(pInfo);
		break;
	case R3964_WAIT_FOR_RX_BUF:
		TRACE_PE("WAIT_FOR_RX_BUF - timeout");
		put_char(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;
		break;
	case R3964_RECEIVING:
		TRACE_PE("RECEIVING - timeout after %d chars",
			 pInfo->rx_position);
		put_char(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;
		break;
	case R3964_WAIT_FOR_RX_REPEAT:
		TRACE_PE("WAIT_FOR_RX_REPEAT - timeout");
		pInfo->state = R3964_IDLE;
		break;
	case R3964_WAIT_FOR_BCC:
		TRACE_PE("WAIT_FOR_BCC - timeout");
		put_char(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;
		break;
	}
}
