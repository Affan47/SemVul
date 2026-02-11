namcos1_install_bank(int start,int end,mem_read_handler hr,mem_write_handler hw,
			  int offset,unsigned char *pointer)
{
	int i;
	for(i=start;i<=end;i++)
	{
		namcos1_bank_element[i].bank_handler_r = hr;
		namcos1_bank_element[i].bank_handler_w = hw;
		namcos1_bank_element[i].bank_offset    = offset;
		namcos1_bank_element[i].bank_pointer   = pointer;
		offset  += 0x2000;
		if(pointer) pointer += 0x2000;
	}
}
