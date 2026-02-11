create_folder_if_necessary() const
{
    boost::filesystem::path folder(kConfigDir);
    if (!boost::filesystem::exists(folder)
        || !boost::filesystem::is_directory(folder))
    {
        if (!boost::filesystem::create_directory(folder))
        {
            throw OkShellException(
                    "Failed to create config directory: " + kConfigDir);
        }
    }
    return;
}
