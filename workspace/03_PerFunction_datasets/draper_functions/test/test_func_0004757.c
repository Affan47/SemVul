process_local_unsure(const vector<string>& command,
        const LocalMatchResult& result) const
{
    mycerr << "Possible matches in local profile:" << endl;
    result.display_multiple();
    size_t choice = integer_choice_input("Choose one number, 0 for none: [1]",
            1, result.match_results.size());
    if (choice == 0)
    {
        mycerr << "Nothing chosen." << endl;
        mycerr << "\n";


        string use_cloud = "n";
        mycerr << kPromotWouldLearnFromCloud << endl;


        if (use_cloud == "y")
        {
            int rv = process_cloud(command);
            if (rv == 3)
            {
                return rv;
            }
            else if (rv == 2)
            {
                mycerr << "\n";
                string add_manually = yes_no_input(kPromptAddManually, "y");
                if (add_manually == "y")
                {
                    rv = process_manual_add(command);
                    return rv;
                }
                else
                {

                    return 2;
                }
            }
            else
            {
                throw OkShellException(
                "process_local_unsure, invalid return value of process_cloud()");
            }
        }
        else
        {
            mycerr << "\n";
            string add_manually = yes_no_input(kPromptAddManually, "y");
            if (add_manually == "y")
            {
                return process_manual_add(command);
            }
            else
            {

                return 2;
            }
        }
    }
    else
    {
        mycerr << "Command " << choice << " chosen." << endl;
        string real_command
            = result.match_results[choice - 1].plain_str_real();
        mycerr << kPrintOutExecuting << endl;
        int rv = exe_system(real_command);
        return rv;
    }
    throw std::logic_error(
            "NormalCommander::process_local_unsure, reached the end");
    return 1;
}
