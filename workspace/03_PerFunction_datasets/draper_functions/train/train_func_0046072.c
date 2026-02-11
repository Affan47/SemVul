activecpu_reset_banking(void)
{
	VERIFY_ACTIVECPU_VOID(activecpu_reset_banking);
	(*cpu[activecpu].intf.set_op_base)(activecpu_get_pc_byte());
}
