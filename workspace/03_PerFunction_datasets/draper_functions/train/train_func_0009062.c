_rtl8821ae_wait_for_h2c_cmd_finish(struct rtl_priv *rtlpriv)
{
	u8 val;
	u16 count = 0;

	do {
		val = rtl_read_byte(rtlpriv, REG_HMETFR);
		mdelay(1);
		count++;
	} while ((val & 0x0F) && (count < 1000));
}
