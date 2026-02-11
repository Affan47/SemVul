readList(const char *filesPath, const char *listname, UBool readContents) {
    Package *listPkg;
    FILE *file;
    const char *listNameEnd;

    if(listname==NULL || listname[0]==0) {
        fprintf(stderr, "missing list file\n");
        return NULL;
    }

    listPkg=new Package();
    if(listPkg==NULL) {
        fprintf(stderr, "icupkg: not enough memory\n");
        exit(U_MEMORY_ALLOCATION_ERROR);
    }

    listNameEnd=strchr(listname, 0);
    if(isListTextFile(listname)) {

        char line[1024];
        char *end;
        const char *start;

        file=fopen(listname, "r");
        if(file==NULL) {
            fprintf(stderr, "icupkg: unable to open list file \"%s\"\n", listname);
            delete listPkg;
            exit(U_FILE_ACCESS_ERROR);
        }

        while(fgets(line, sizeof(line), file)) {

            end=strchr(line, '#');
            if(end!=NULL) {
                *end=0;
            } else {

                end=strchr(line, 0);
                while(line<end && (*(end-1)=='\r' || *(end-1)=='\n')) {
                    *--end=0;
                }
            }


            start=u_skipWhitespace(line);
            if(*start==0 || NULL!=strchr(U_PKG_RESERVED_CHARS, *start)) {
                continue;
            }


            for(;;) {

                for(end=(char *)start; *end!=0 && *end!=' ' && *end!='\t'; ++end) {}
                if(*end==0) {

                    end=NULL;
                } else {

                    *end=0;
                }
                if(readContents) {
                    listPkg->addFile(filesPath, start);
                } else {
                    listPkg->addItem(start);
                }


                if(end==NULL || *(start=u_skipWhitespace(end+1))==0) {
                    break;
                }
            }
        }
        fclose(file);
    } else if((listNameEnd-listname)>4 && 0==memcmp(listNameEnd-4, ".dat", 4)) {

        listPkg->readPackage(listname);
    } else {

        if(readContents) {
            listPkg->addFile(filesPath, listname);
        } else {
            listPkg->addItem(listname);
        }
    }

    return listPkg;
}
