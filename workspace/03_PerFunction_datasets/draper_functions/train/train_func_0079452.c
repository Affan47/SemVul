generateTaxonomy()
{


    vector<string> path = PluginHostAdapter::getPluginPath();
    string libfragment = "/lib/";
    vector<string> catpath;

    string suffix = "cat";

    for (vector<string>::iterator i = path.begin();
         i != path.end(); ++i) {


        string dir = *i;
        string::size_type li = dir.find(libfragment);

        if (li != string::npos) {
            catpath.push_back
                (dir.substr(0, li)
                 + "/share/"
                 + dir.substr(li + libfragment.length()));
        }

        catpath.push_back(dir);
    }

    char buffer[1024];

    for (vector<string>::iterator i = catpath.begin();
         i != catpath.end(); ++i) {

        vector<string> files = listFiles(*i, suffix);

        for (vector<string>::iterator fi = files.begin();
             fi != files.end(); ++fi) {

            string filepath = splicePath(*i, *fi);
            ifstream is(filepath.c_str(), ifstream::in | ifstream::binary);

            if (is.fail()) {

                continue;
            }


            while (!!is.getline(buffer, 1024)) {

                string line(buffer);


                string::size_type di = line.find("::");
                if (di == string::npos) continue;

                string id = line.substr(0, di);
                string encodedCat = line.substr(di + 2);

                if (id.substr(0, 5) != "vamp:") continue;
                id = id.substr(5);

                while (encodedCat.length() >= 1 &&
                       encodedCat[encodedCat.length()-1] == '\r') {
                    encodedCat = encodedCat.substr(0, encodedCat.length()-1);
                }


                PluginCategoryHierarchy category;
                string::size_type ai;
                while ((ai = encodedCat.find(" > ")) != string::npos) {
                    category.push_back(encodedCat.substr(0, ai));
                    encodedCat = encodedCat.substr(ai + 3);
                }
                if (encodedCat != "") category.push_back(encodedCat);

                m_taxonomy[id] = category;
            }
        }
    }
}
