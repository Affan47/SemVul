readString (std::istream &s) {
    int index = readWord (s) ;
    if (loadpass == 1) {
        return "" ;
    }
    if (index < 0 || index >= stringvec.size()) {
        std::cerr << "Invalid string index " << index << "\n" ;
        abort() ;
    }
    return lookupString (index) ;
}
