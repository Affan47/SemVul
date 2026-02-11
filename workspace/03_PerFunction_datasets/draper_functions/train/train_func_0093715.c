dxfString(int gc, const char* value) const {
    if (value==NULL) {
#ifndef __GCC2x__

#endif
    }
    m_ofile << (gc<10 ? "  " : (gc<100 ? " " : "")) << gc << "\n"
    << value << "\n";
}
