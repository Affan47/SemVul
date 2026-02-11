crc32_test_exec ( void ) {

	crc32_ok ( &empty_test );
	crc32_ok ( &hw_test );
	crc32_ok ( &hw_split_part1_test );
	crc32_ok ( &hw_split_part2_test );
}
