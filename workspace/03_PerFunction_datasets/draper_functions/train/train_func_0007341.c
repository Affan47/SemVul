parse_route(unsigned char *route, unsigned int *route_len, char *str)
{
    struct in_addr ip;
    unsigned int i = 0;
    unsigned int j;
    unsigned int n = 0;
    unsigned int route_ptr = 256;
    char c;

    route += 3;
    while (str[i] != '\0')
    {
        for (j = i; isalnum(str[j]) || str[j] == '.'; j++);
        switch(c = str[j])
        {
            case '\0':
            case '/':
                if (n >= 62)
                {
                    fprintf(stderr, "too long route\n");
                    fail_parse_route();
                }
                str[j] = '\0';
                if (inet_aton(str+i, &ip))
                {
                    memcpy(route+4*n, &ip.s_addr, 4);
                    n++;
                    if (c == '/')
                        str[j++] = '/';
                    break;
                }
                fprintf(stderr, "invalid IP address in route\n");
                fail_parse_route();
            case ':':
                if ((!i) && j && j < 4)
                {
                    sscanf(str, "%u:%n", &route_ptr, &i);
                    if (i == ++j)
                    {
                        if (route_ptr < 256)
                            break;
                    }
                }
            default:
                fail_parse_route();
        }
        i = j;
    }
    if (route_ptr == 256)
        route[-1] = (unsigned char) ( n ? 8 : 4 );
    else
        route[-1] = (unsigned char) route_ptr;
    *route_len = 4*n + 3;
    route[-2] = (unsigned char) *route_len;
}
