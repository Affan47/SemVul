to_utf8_test()
{
    print_utf8(0x41UL);
    print_utf8(0xF7UL);
    print_utf8(0x3c0UL);
    print_utf8(0x16059UL);
    print_utf8(0x7fffffffUL);
    try
    {
	print_utf8(0x80000000UL);
    }
    catch (std::runtime_error& e)
    {
	std::cout << "0x80000000: " << e.what() << std::endl;
    }
}
