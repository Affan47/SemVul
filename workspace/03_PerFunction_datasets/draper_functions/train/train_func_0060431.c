ar5416IsInterruptPending(struct ath_hal *ah)
{
	a_uint32_t host_isr =
		ioread32_mac(AR_INTR_ASYNC_CAUSE);


	return ((host_isr != AR_INTR_SPURIOUS) && (host_isr & AR_INTR_MAC_IRQ));
}
