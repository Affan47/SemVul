removeFile (const std::string &filename){
    FileMap::iterator i = files.find (filename) ;
    if (i != files.end()) {
        LineMap::iterator l = i->second->begin() ;
        while (l != i->second->end()) {
            delete l->second ;
            l++ ;
        }
        files.erase (i) ;
    }
    lastfilename = "" ;
}
