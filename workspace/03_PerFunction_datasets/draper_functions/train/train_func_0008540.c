parse_pages_options(
    int argc, char* argv[], int& cur_arg)
{
    std::vector<PageSpec> result;
    while (1)
    {
        if ((cur_arg < argc) && (strcmp(argv[cur_arg], "--") == 0))
        {
            break;
        }
        if (cur_arg + 2 >= argc)
        {
            usage("insufficient arguments to --pages");
        }
        char const* file = argv[cur_arg++];
        char const* password = 0;
        char const* range = argv[cur_arg++];
        if (strncmp(range, "--password=", 11) == 0)
        {

            if (cur_arg + 1 >= argc)
            {
                usage("insufficient arguments to --pages");
            }
            password = range + 11;
            range = argv[cur_arg++];
        }


        bool range_omitted = false;
        if (strcmp(range, "--") == 0)
        {

            QTC::TC("qpdf", "qpdf pages range omitted at end");
            range_omitted = true;
        }
        else
        {
            try
            {
                parse_numrange(range, 0, true);
            }
            catch (std::runtime_error& e1)
            {

                try
                {
                    fclose(QUtil::safe_fopen(range, "rb"));

                    QTC::TC("qpdf", "qpdf pages range omitted in middle");
                    range_omitted = true;
                }
                catch (std::runtime_error& e2)
                {


                }
            }
        }
        if (range_omitted)
        {
            --cur_arg;
            range = "1-z";
        }

        result.push_back(PageSpec(file, password, range));
    }
    return result;
}
