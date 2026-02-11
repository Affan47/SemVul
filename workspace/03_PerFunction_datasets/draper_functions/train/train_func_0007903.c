main(int argc, char* argv[])
{
    try
    {
        log_init();

        cxxtools::Arg<unsigned> nn(argc, argv, 'n', 100000);
        cxxtools::Arg<unsigned> I(argc, argv, 'I', nn);
        cxxtools::Arg<unsigned> D(argc, argv, 'D', nn);
        cxxtools::Arg<unsigned> C(argc, argv, 'C', nn);
        cxxtools::Arg<bool> fileoutput(argc, argv, 'f');

        std::cout << "benchmark serializer with " << I.getValue() << " int vector " << D.getValue() << " double vector and " << C.getValue() << " custom vector iterations\n\n"
                     "options:\n"
                     "   -n <number>       specify number of default iterations\n"
                     "   -I <number>       specify number of iterations for int vector\n"
                     "   -D <number>       specify number of iterations for double vector\n"
                     "   -C <number>       specify number of iterations for custom object\n"
                     "   -f                write serialized output to files\n" << std::endl;

        if (I.getValue() > 0)
            benchVector<int>("int", I, 1, fileoutput);

        if (D.getValue() > 0)
            benchVector<double>("double", D, 0.25, fileoutput);

        if (C.getValue() > 0)
        {
            std::cout << "vector of custom objects:" << std::endl;

            TestObject obj;
            std::vector<TestObject> v;
            for (unsigned n = 0; n < C; ++n)
            {
                obj.intValue = n;
                obj.stringValue = cxxtools::convert<std::string>(n);
                obj.doubleValue = sqrt(static_cast<double>(n));
                obj.boolValue = n&1;
                v.push_back(obj);
            }

            std::cout << "xml:" << std::endl;
            benchXmlSerialization(v, fileoutput ? "custobject.xml" : 0);

            std::cout << "json:" << std::endl;
            benchJsonSerialization(v, fileoutput ? "custobject.json" : 0);

            std::cout << "bin:" << std::endl;
            benchBinSerialization(v, fileoutput ? "custobject.bin" : 0);
        }

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
