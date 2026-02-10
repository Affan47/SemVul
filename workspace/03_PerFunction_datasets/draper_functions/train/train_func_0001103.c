put_checksum(u8 *check_string, int length)
{
	dprintk(verbose, DST_CA_DEBUG, 1, " Computing string checksum.");
	dprintk(verbose, DST_CA_DEBUG, 1, "  -> string length : 0x%02x", length);
	check_string[length] = dst_check_sum (check_string, length);
	dprintk(verbose, DST_CA_DEBUG, 1, "  -> checksum      : 0x%02x", check_string[length]);
}
