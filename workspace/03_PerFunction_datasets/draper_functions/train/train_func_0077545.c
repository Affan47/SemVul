find_reloc(int sh_index)
{
    struct elf_shdr *sec;
    int i;

    for(i = 0; i < ehdr.e_shnum; i++) {
        sec = &shdr[i];
        if (sec->sh_type == SHT_RELOC && sec->sh_info == sh_index)
            return i;
    }
    return 0;
}
