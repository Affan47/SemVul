main() {


    FILE* confFile = fopen("config","r");
    char* confFileContents = fileAsString(confFile);


    loadConf(confFileContents);
    free(confFileContents);


    while(1) {
whileStart:
        printf(">> ");
        if(fgets(entry, BUFSIZE, stdin)) {
            if(impCharInd(entry, &isspace, 0) == -1)
                goto whileStart;
            switch(entry[impCharInd(entry, &isspace, 0)]) {
                case 'q':
                    goto exitLoop;
                case 'c':
                    doConversion();
                    break;
                case 'a':
                    addConversion();
                    break;
                case 'h':
                    printHelp();
                    break;
                case '?':
                    printHelp();
                    break;
                default:
                    break;
            }
        }
    }
exitLoop:


    return 0;
}
