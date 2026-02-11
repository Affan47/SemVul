wusb_key_derive_verify(void)
{
	int result = 0;
	struct wusb_keydvt_out keydvt_out;


	struct wusb_keydvt_in stv_keydvt_in_a1 = {
		.hnonce = {
			0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
			0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
		},
		.dnonce = {
			0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
			0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f
		}
	};

	result = wusb_key_derive(&keydvt_out, stv_key_a1, &stv_keydvt_n_a1,
				 &stv_keydvt_in_a1);
	if (result < 0)
		printk(KERN_ERR "E: WUSB key derivation test: "
		       "derivation failed: %d\n", result);
	if (memcmp(&stv_keydvt_out_a1, &keydvt_out, sizeof(keydvt_out))) {
		printk(KERN_ERR "E: WUSB key derivation test: "
		       "mismatch between key derivation result "
		       "and WUSB1.0[A1] Errata 2006/12\n");
		printk(KERN_ERR "E: keydvt in: key\n");
		wusb_key_dump(stv_key_a1, sizeof(stv_key_a1));
		printk(KERN_ERR "E: keydvt in: nonce\n");
		wusb_key_dump( &stv_keydvt_n_a1, sizeof(stv_keydvt_n_a1));
		printk(KERN_ERR "E: keydvt in: hnonce & dnonce\n");
		wusb_key_dump(&stv_keydvt_in_a1, sizeof(stv_keydvt_in_a1));
		printk(KERN_ERR "E: keydvt out: KCK\n");
		wusb_key_dump(&keydvt_out.kck, sizeof(keydvt_out.kck));
		printk(KERN_ERR "E: keydvt out: PTK\n");
		wusb_key_dump(&keydvt_out.ptk, sizeof(keydvt_out.ptk));
		result = -EINVAL;
	} else
		result = 0;
	return result;
}
