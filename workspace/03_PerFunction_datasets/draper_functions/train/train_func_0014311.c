unpack_elf_symbol_info(SymbolSection * section, U4_T index, SymbolInfo * info) {
    memset(info, 0, sizeof(SymbolInfo));
    if (index >= section->mSymCount) exception(ERR_INV_FORMAT);
    info->mSymSection = section;
    if (section->mFile->elf64) {
        Elf64_Sym s = ((Elf64_Sym *)section->mSymPool)[index];
        if (section->mFile->byte_swap) {
            SWAP(s.st_name);
            SWAP(s.st_shndx);
            SWAP(s.st_size);
            SWAP(s.st_value);
        }
        info->mSectionIndex = s.st_shndx;
        if (s.st_shndx > 0 && s.st_shndx < section->mFile->section_cnt) {
            info->mSection = section->mFile->sections + s.st_shndx;
        }
        if (s.st_name > 0) {
            if (s.st_name >= section->mStrPoolSize) exception(ERR_INV_FORMAT);
            info->mName = section->mStrPool + s.st_name;
        }
        info->mBind = ELF64_ST_BIND(s.st_info);
        info->mType = ELF64_ST_TYPE(s.st_info);
        info->mValue = s.st_value;
        info->mSize = s.st_size;
    }
    else {
        Elf32_Sym s = ((Elf32_Sym *)section->mSymPool)[index];
        if (section->mFile->byte_swap) {
            SWAP(s.st_name);
            SWAP(s.st_shndx);
            SWAP(s.st_size);
            SWAP(s.st_value);
        }
        info->mSectionIndex = s.st_shndx;
        if (s.st_shndx > 0 && s.st_shndx < section->mFile->section_cnt) {
            info->mSection = section->mFile->sections + s.st_shndx;
        }
        if (s.st_name > 0) {
            if (s.st_name >= section->mStrPoolSize) exception(ERR_INV_FORMAT);
            info->mName = section->mStrPool + s.st_name;
        }
        info->mBind = ELF32_ST_BIND(s.st_info);
        info->mType = ELF32_ST_TYPE(s.st_info);
        info->mValue = s.st_value;
        info->mSize = s.st_size;
    }
}
