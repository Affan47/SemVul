main(int argc, char *argv[])
{
    FILE *iplist1 = NULL;
    FILE *iplist2 = NULL;
    plist_t root_node1 = NULL;
    plist_t root_node2 = NULL;
    char *plist_1 = NULL;
    char *plist_2 = NULL;
    int size_in1 = 0;
    int size_in2 = 0;
    char *file_in1 = NULL;
    char *file_in2 = NULL;
    int res = 0;

    struct stat *filestats1 = (struct stat *) malloc(sizeof(struct stat));
    struct stat *filestats2 = (struct stat *) malloc(sizeof(struct stat));

    if (argc!= 3)
    {
        printf("Wrong input\n");
        return 1;
    }

    file_in1 = argv[1];
    file_in2 = argv[2];


    iplist1 = fopen(file_in1, "rb");
    iplist2 = fopen(file_in2, "rb");

    if (!iplist1 || !iplist2)
    {
        printf("File does not exists\n");
        return 2;
    }

    stat(file_in1, filestats1);
    stat(file_in2, filestats2);

    size_in1 = filestats1->st_size;
    size_in2 = filestats2->st_size;

    plist_1 = (char *) malloc(sizeof(char) * (size_in1 + 1));
    plist_2 = (char *) malloc(sizeof(char) * (size_in2 + 1));

    fread(plist_1, sizeof(char), size_in1, iplist1);
    fread(plist_2, sizeof(char), size_in2, iplist2);

    fclose(iplist1);
    fclose(iplist2);

    if (memcmp(plist_1, "bplist00", 8) == 0)
        plist_from_bin(plist_1, size_in1, &root_node1);
    else
        plist_from_xml(plist_1, size_in1, &root_node1);

    if (memcmp(plist_2, "bplist00", 8) == 0)
        plist_from_bin(plist_2, size_in2, &root_node2);
    else
        plist_from_xml(plist_2, size_in2, &root_node2);

    if (!root_node1 || !root_node2)
    {
        printf("PList parsing failed\n");
        return 3;
    }
    else
        printf("PList parsing succeeded\n");

    res = compare_plist(root_node1, root_node2);


    plist_free(root_node1);
    plist_free(root_node2);

    free(plist_1);
    free(plist_2);
    free(filestats1);
    free(filestats2);

    return !res;
}
