i2c_select ( struct bit_basher *basher, struct i2c_device *i2cdev,
			unsigned int offset, unsigned int direction ) {
	unsigned int address;
	int shift;
	unsigned int byte;
	int rc;

	i2c_start ( basher );


	address = ( ( ( i2cdev->dev_addr |
			( offset >> ( 8 * i2cdev->word_addr_len ) ) ) << 1 )
		    | direction );


	for ( shift = ( 8 * ( i2cdev->dev_addr_len - 1 ) ) ;
	      shift >= 0 ; shift -= 8 ) {
		byte = ( ( address >> shift ) & 0xff );
		if ( ( rc = i2c_send_byte ( basher, byte ) ) != 0 )
			return rc;
	}

	return 0;
}
