update_added_starttabbing_command(FbTk::ResourceManager& rm,
        const FbTk::FbString& keyfilename, const FbTk::FbString& appsfilename) {
    string whole_keyfile = read_file(keyfilename);
    string new_keyfile = "";

    new_keyfile += "!mouse actions added by fluxbox-update_configs\n";
    new_keyfile += "OnTitlebar Mouse2 :StartTabbing\n\n";
    new_keyfile += whole_keyfile;

    write_file(keyfilename, new_keyfile);
}
