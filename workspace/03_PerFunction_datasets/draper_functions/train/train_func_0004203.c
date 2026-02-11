readConf(string configfile) {
    int n = -1;
    string line, fn(configfile);
    map<string,string>::iterator it;
    string op;
    ifstream cfgfile( fn.c_str() );
    if (cfgfile) {
        while (getline( cfgfile, line )) {
            it = options.begin();
            while (it != options.end()) {
                op = it->first;
                n = line.find(op);
                if (n == 0)
                    options[op] = parseOption(line, op);
                it++;
            }
        }
        cfgfile.close();

        return true;
    } else {
        error = "Cannot read configuration file: " + configfile;
        return false;
    }
}
