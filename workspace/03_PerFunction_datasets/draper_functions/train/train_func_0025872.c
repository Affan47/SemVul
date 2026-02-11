rip_entry_print_v2(register const struct rip_netinfo *ni)
{
	register u_char *p;
	register u_short family;
	u_char buf[RIP_AUTHLEN];

	family = EXTRACT_16BITS(&ni->rip_family);
	if (family == 0xFFFF) {
                if (EXTRACT_16BITS(&ni->rip_tag) == 2) {
			memcpy(buf, &ni->rip_dest, sizeof(buf));
			buf[sizeof(buf)-1] = '\0';
			for (p = buf; *p; p++) {
				if (!isprint(*p))
					break;
			}
                        printf("\n\t  Simple Text Authentication data: %s", buf);
                } else {
			printf("\n\t  Unknown (%u) Authentication data:",
			       EXTRACT_16BITS(&ni->rip_tag));
                        print_unknown_data((u_int8_t *)&ni->rip_dest,"\n\t  ",RIP_AUTHLEN);
		}
	} else if (family != AF_INET) {
		printf("\n\t  AFI: %u", family);
                print_unknown_data((u_int8_t *)&ni->rip_tag,"\n\t  ",RIP_ROUTELEN-2);
		return;
	} else {
		printf("\n\t  AFI: IPv4: %15s/%-2d, tag 0x%04x, metric: %u, next-hop: ",
                       ipaddr_string(&ni->rip_dest),
		       mask2plen(EXTRACT_32BITS(&ni->rip_dest_mask)),
                       EXTRACT_16BITS(&ni->rip_tag),
                       EXTRACT_32BITS(&ni->rip_metric));
		if (EXTRACT_32BITS(&ni->rip_router))
			printf("%s", ipaddr_string(&ni->rip_router));
                else
                    printf("self");
	}
}
