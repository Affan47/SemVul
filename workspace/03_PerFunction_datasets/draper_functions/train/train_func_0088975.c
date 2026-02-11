load_cluster_nodes(char *pathname, struct sockaddr_in *nodes) {
    char buf[MAX_NODE_LINE];
    int line = 1;
    int i = 0;
    FILE *f;

    if ((f = fopen(pathname, "rb")) == NULL) {
        printf("Cannot open %s: %m\n", pathname);
        exit(1);
    }

    while (fgets(buf, sizeof(buf), f)) {
        struct hostent *he;
        char user[32];
        char host[64];
        int port;
        int cpu;
        int n, j;

        n = sscanf(buf, "%31[a-zA-Z0-9._-]@%63[a-zA-Z0-9._-]:%d^%d",
            &user, &host, &port, &cpu);

        if (n != 4) {
            printf("Error in %s on line %d: %s", pathname, line, buf);
            printf("Format: user@host:port^cpu\n");
            exit(1);
        }

        if (!(he = gethostbyname((const char *) &host))) {
            printf("Cannot resolve host: %s\n", host);
            exit(1);
        }

        for (j = 0; j < cpu; j++, i++) {
            if (i >= MAX_CLUSTER_NODES) {
                printf("Too many cluster nodes. You should recompile\n");
                printf("EPSILON with larger MAX_CLUSTER_NODES value.\n");
                exit(1);
            }


            memset(&nodes[i], 0, sizeof(struct sockaddr_in));
            nodes[i].sin_family = AF_INET;
            nodes[i].sin_port = htons(port);
            memcpy(&nodes[i].sin_addr, he->h_addr_list[0], he->h_length);
        }

        line++;
    }

    fclose(f);
    return i;
}
