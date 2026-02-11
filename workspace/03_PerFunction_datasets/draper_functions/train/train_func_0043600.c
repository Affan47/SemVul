main(int argc, char** argv)
{
    ParserOptions parser_options = {
        false
    };


    char *infilename = NULL;

    unsigned positional_count = 0;


    for (unsigned i = 1; i < argc; ++i)
    {
        if (!strcmp("-h", argv[i]) || !strcmp("--help", argv[i]))
        {
            std::cout<<usage_string;
            return 0;
        }
#if defined(YYDEBUG)

        else if (!strcmp("-d", argv[i]) || !strcmp("--debug", argv[i]))
            yydebug = 1;
#endif

        else
        {
            switch(positional_count)
            {

                case 0:
                    infilename = argv[i];
                    break;
                default:
                    std::cerr<<"Unknown option \""<<argv[i]<<"\"";
                    return 0;
            }

            ++positional_count;
        }
    }


    if (infilename != NULL)
    {
        yyin = fopen(infilename, "r");
        if (yyin == NULL)
        {
            perror ("Failed to open file");
            return 0;
        }

        parser_options.file_input = true;
    }


    try {
        yyparse(parser_options);

        if (!parser_options.file_input)
            std::cout<<std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Encountered exception while parsing: "<<e.what()<<'\n';
        do_cleanup();
    };


    return 0;
}
