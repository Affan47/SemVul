x11CursorShape(const QString &name)
    {
        static QHash<QString, int> shapes;


        if (shapes.isEmpty())
        {
            int num = XC_num_glyphs / 2;
            shapes.reserve(num + 5);

            for (int i = 0; i < num; ++i)
                shapes.insert(standard_names[i], i << 1);


            shapes.insert("size_all",      XC_fleur);
            shapes.insert("up_arrow",      XC_center_ptr);
            shapes.insert("ibeam",         XC_xterm);
            shapes.insert("wait",          XC_watch);
            shapes.insert("pointing_hand", XC_hand2);
        }

        return shapes.value(name, -1);
    }
