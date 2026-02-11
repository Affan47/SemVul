IRQHandler_3812(int n,int irq)
{
	if (intf_3812->handler[n]) (intf_3812->handler[n])(irq ? ASSERT_LINE : CLEAR_LINE);
}
