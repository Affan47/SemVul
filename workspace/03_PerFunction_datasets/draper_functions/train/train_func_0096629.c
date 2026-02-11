fopen_wrapper_test()
{
    try
    {
	std::cout << "before fopen" << std::endl;
	FILE* f = QUtil::safe_fopen("/this/file/does/not/exist", "r");
	std::cout << "after fopen" << std::endl;
	(void) fclose(f);
    }
    catch (std::runtime_error& s)
    {
	std::cout << "exception: " << s.what() << std::endl;
    }
}
