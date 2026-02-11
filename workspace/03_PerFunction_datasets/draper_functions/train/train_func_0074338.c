process_manual_add(const vector<string>& command) const
{
    mycerr << "\n";
    mycerr
    << "Write the " << boldface("HUMAN") << " command template." << endl;
    mycerr << "EXAMPLE: $ ok recursively delete " << boldface("<arg1>")
           << " files" << endl;
    string human_command = command_input("$ ok");
    mycerr << "\n";
    mycerr << "Write the " << boldface("REAL") << " command template." << endl;
    mycerr << "EXAMPLE: $ find . -name \"*."
           << boldface("<arg1>") << "\" | xargs rm -rf" << endl;
    string real_command = command_input("$");
    mycerr << "\n";
    add_to_local_and_cloud(human_command, real_command);
    return 3;
}
