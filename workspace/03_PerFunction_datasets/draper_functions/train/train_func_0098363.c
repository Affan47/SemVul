operator()(const dbg::source_pos &a, const dbg::source_pos &b)
            const
        {
            if (a.file == b.file)
            {
                if (a.func == b.func)
                {
                    return a.line < b.line;
                }
                else
                {
                    return a.func < b.func;
                }
            }
            else
            {
                return a.file < b.file;
            }
        }
