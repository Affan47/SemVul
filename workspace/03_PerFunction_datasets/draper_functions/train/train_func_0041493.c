TestInit(const char *ProgName, void (*private_usage)(void), int (*private_parser)(int ac, char *av[]))
{

    H5Eget_auto2(H5E_DEFAULT, PrintErrorStackFunc, PrintErrorStackData);


    PrintErrorStackOff();


    TestProgName = ProgName;
    if (NULL != private_usage)
	TestPrivateUsage = private_usage;
    if (NULL != private_parser)
	TestPrivateParser = private_parser;
}
