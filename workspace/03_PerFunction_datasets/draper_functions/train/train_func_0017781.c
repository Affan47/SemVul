show (string cmd) {
    if (cmd == "") {
       status (cmd) ;
       return ;
    }
    string what ;
    int index = 0 ;
    while (index < cmd.size()) {
        what = getString (cmd, index) ;
        if (what == "blocks") {
            for (int i = 0 ; i < blocks.size() ; i++) {
                DBlock *block = blocks[i] ;
                if (!block->systemblock) {
                    std::cout << blocktype (block) << " " << block->fullname.c_str() + 1 << " in file " << block->filename << " at line " << block->lineno << '\n' ;
                }
            }
        } else if (what == "allblocks") {
            for (int i = 0 ; i < blocks.size() ; i++) {
                DBlock *block = blocks[i] ;
                std::cout << blocktype (block) << " " << block->fullname.c_str() + 1 << " in file " << block->filename << " at line " << block->lineno << '\n' ;
            }
        } else if (what == "breaks") {
            status(cmd) ;
        } else if (what == "files") {
            listFiles(cmd) ;
        } else if (what == "stack") {
            where(cmd) ;
        } else if (what == "threads") {
            listThreads(cmd) ;
        } else if (what == "vars") {
            showvars(cmd) ;
        }
    }
}
