replace_arguments(const CommandProfileEntry& profile_entry,
        const vector<string>& command, CloudMatchEntry& result_entry) const
{


    result_entry.human_command = profile_entry.human_profile;
    result_entry.real_command = profile_entry.real_profile;

    vector<size_t> indexes_human;
    find_arg_indexes(profile_entry.human_profile, indexes_human);

    vector<size_t> indexes_real;
    find_arg_indexes(profile_entry.real_profile, indexes_real);

    size_t command_size = command.size();
    for (size_t idx_human : indexes_human)
    {
        if (idx_human >= command_size)
        {
            return false;
        }
        const string& arg_str = profile_entry.human_profile[idx_human].impl;
        const string& sub_str = command[idx_human];

        result_entry.human_command[idx_human].impl = sub_str;

        for (size_t idx_real : indexes_real)
        {
            boost::replace_all(result_entry.real_command[idx_real].impl,
                    arg_str, sub_str);
        }
    }
    return true;
}
