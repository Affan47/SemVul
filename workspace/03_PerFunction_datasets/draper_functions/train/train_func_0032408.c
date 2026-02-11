parse_terminator(vector<string>& args)
    {
        vector<option> result;
        const string& tok = args[0];
        if (tok == "--")
        {
            for(unsigned i = 1; i < args.size(); ++i)
            {
                option opt;
                opt.value.push_back(args[i]);
                opt.original_tokens.push_back(args[i]);
                opt.position_key = INT_MAX;
                result.push_back(opt);
            }
            args.clear();
        }
        return result;
    }
