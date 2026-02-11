APar_MetadataFileDump(const char* m4aFile) {
    char* dump_file_name = (char*) malloc(sizeof(char) * (strlen(m4aFile) + 12 + 1));
    memset(dump_file_name, 0, sizeof(char) * (strlen(m4aFile) + 12 + 1));

    FILE* dump_file;
    AtomicInfo* userdata_atom = APar_FindAtom("moov.udta", false, SIMPLE_ATOM, 0);


    if (userdata_atom != NULL) {
        char* dump_buffer = (char*) malloc(sizeof(char) * userdata_atom->AtomicLength + 1);
        memset(dump_buffer, 0, sizeof(char) * userdata_atom->AtomicLength + 1);

        APar_DeriveNewPath(m4aFile, dump_file_name, 1, "-dump-", ".raw");
        dump_file = APar_OpenFile(dump_file_name, "wb");
        if (dump_file != NULL) {


            fseeko(source_file, userdata_atom->AtomicStart, SEEK_SET);
            fread(dump_buffer, 1, (size_t) userdata_atom->AtomicLength, source_file);

            fwrite(dump_buffer, (size_t) userdata_atom->AtomicLength, 1, dump_file);
            fclose(dump_file);

            fprintf(stdout, " Metadata dumped to %s\n", dump_file_name);
        }
        free(dump_buffer);
        dump_buffer = NULL;

    }
    else {
        fprintf(stdout, "AtomicParsley error: no moov.udta atom was found to dump out to file.\n");
    }

    return;
}
