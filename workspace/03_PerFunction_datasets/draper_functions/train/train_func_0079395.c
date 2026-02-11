process_local_sure(const LocalMatchResult& result,
        bool interactive) const
{

    if (interactive)
    {
        mycerr << "Found match in local profile." << endl;
        mycerr << "\n";
        mycerr << "  " << os_label(kOSHuman) << kEXE << " "
               << result.match_results[0].color_str_human() << endl;
        mycerr << "  " << os_label(kOSLinux)
               << result.match_results[0].color_str_real() << endl;
        mycerr << "\n";
        mycerr << kPrintOutExecuting << endl;
    }
    string real_command
        = result.match_results[0].plain_str_real();
    int rv = exe_system(real_command);
    return rv;
}
