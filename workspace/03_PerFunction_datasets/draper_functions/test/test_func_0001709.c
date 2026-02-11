get_COMMON_PARENT(dll_header *THIS){
    int key = (int)(THIS->key) >> 16;
    if (aisc_d_flags[key] == 0) return 0;
    if(!((THIS->parent))){return 0; }
    return (dllheader_ext *)THIS->parent->parent;
}
