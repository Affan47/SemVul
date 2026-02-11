init_only_once() {
    vector<string> empty;
    vector<string> temp;


    temp.push_back("radius");
    temp.push_back("rad");
    keywords["radius"] = keywords["rad"] = keyword(empty, temp, false, RADIUS);

    temp.clear();
    temp.push_back("from");
    keywords["from"] = keyword(empty, temp, false, FROM);

    temp.clear();
    temp.push_back("thru");
    temp.push_back("through");
    keywords["thru"] = keywords["through"] = keyword(empty, temp, false, THRU);

    temp.clear();
    temp.push_back("to");
    keywords["to"] = keyword(empty, temp, false, TO);

    temp.clear();
    temp.push_back("by");
    keywords["by"] = keyword(empty, temp, false, BY);

    temp.clear();
    temp.push_back("until");
    keywords["until"] = keyword(empty, temp, false, UNTIL);

    temp.clear();
    temp.push_back("do");
    keywords["do"] = keyword(empty, temp, false, DO);

    temp.clear();
    temp.push_back("x");
    keywords["x"] = keyword(empty, temp, false, XDIM);

    temp.clear();
    temp.push_back("y");
    keywords["y"] = keyword(empty, temp, false, YDIM);

    temp.clear();
    temp.push_back("base");
    keywords["base"] = keyword(empty, temp, false, BASE);

    temp.clear();
    temp.push_back("ht");
    keywords["ht"] = keyword(empty, temp, false, HT);

    temp.clear();
    temp.push_back("wid");
    keywords["wid"] = keyword(empty, temp, false, WID);

    temp.clear();
    temp.push_back("at");
    keywords["plot"] = keyword(temp, empty, true, PLOT);
}
