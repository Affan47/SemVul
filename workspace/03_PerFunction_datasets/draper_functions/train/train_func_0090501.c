file (string cmd) {
    int index = 0 ;
    string filename = getString (cmd, index) ;
    if (filename == "") {
        std::cout << "Current file is " << currentFile->name << "\n" ;
    } else {
        currentFile = findFile (filename) ;
    }
}
